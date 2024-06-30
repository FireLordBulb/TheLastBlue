#include "BlitToTarget.h"
#include "GlyphCompute/Public/BlitToTarget/BlitToTarget.h"
#include "PixelShaderUtils.h"
#include "MeshPassProcessor.inl"
#include "StaticMeshResources.h"
#include "DynamicMeshBuilder.h"
#include "RenderGraphResources.h"
#include "GlobalShader.h"
#include "UnifiedBuffer.h"
#include "CanvasTypes.h"
#include "MeshDrawShaderBindings.h"
#include "RHIGPUReadback.h"
#include "MaterialShader.h"

DECLARE_STATS_GROUP(TEXT("BlitToTarget"), STATGROUP_BlitToTarget, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("BlitToTarget Execute"), STAT_BlitToTarget_Execute, STATGROUP_BlitToTarget);

// This class carries our parameter declarations and acts as the bridge between cpp and HLSL.
class GLYPHCOMPUTE_API FBlitToTarget: public FGlobalShader
{
public:
	
	DECLARE_GLOBAL_SHADER(FBlitToTarget);
	SHADER_USE_PARAMETER_STRUCT(FBlitToTarget, FGlobalShader);
	

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		/*
		* Here's where you define one or more of the input parameters for your shader.
		* Some examples:
		*/
		// SHADER_PARAMETER(uint32, MyUint32) // On the shader side: uint32 MyUint32;
		// SHADER_PARAMETER(FVector3f, MyVector) // On the shader side: float3 MyVector;

		//SHADER_PARAMETER_TEXTURE(Texture2D, InputTexture) // On the shader side: Texture2D<float4> MyTexture; (float4 should be whatever you expect each pixel in the texture to be, in this case float4(R,G,B,A) for 4 channels)
		// SHADER_PARAMETER_SAMPLER(SamplerState, MyTextureSampler) // On the shader side: SamplerState MySampler; // CPP side: TStaticSamplerState<ESamplerFilter::SF_Bilinear>::GetRHI();

		// SHADER_PARAMETER_ARRAY(float, MyFloatArray, [3]) // On the shader side: float MyFloatArray[3];

		// SHADER_PARAMETER_UAV(RWTexture2D<FVector4f>, MyTextureUAV) // On the shader side: RWTexture2D<float4> MyTextureUAV;
		// SHADER_PARAMETER_UAV(RWStructuredBuffer<FMyCustomStruct>, MyCustomStructs) // On the shader side: RWStructuredBuffer<FMyCustomStruct> MyCustomStructs;
		// SHADER_PARAMETER_UAV(RWBuffer<FMyCustomStruct>, MyCustomStructs) // On the shader side: RWBuffer<FMyCustomStruct> MyCustomStructs;

		// SHADER_PARAMETER_SRV(StructuredBuffer<FMyCustomStruct>, MyCustomStructs) // On the shader side: StructuredBuffer<FMyCustomStruct> MyCustomStructs;
		// SHADER_PARAMETER_SRV(Buffer<FMyCustomStruct>, MyCustomStructs) // On the shader side: Buffer<FMyCustomStruct> MyCustomStructs;
		SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D, InputTexture) // On the shader side: Texture2D<float4> MyReadOnlyTexture;

		// SHADER_PARAMETER_STRUCT_REF(FMyCustomStruct, MyCustomStruct)

		
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RenderTarget)
		

	END_SHADER_PARAMETER_STRUCT()
private:
};

// This will tell the engine to create the shader and where the shader entry point is.
//                            ShaderType                            ShaderPath                     Shader function name    Type
IMPLEMENT_GLOBAL_SHADER(FBlitToTarget, "/GlyphComputeShaders/BlitToTarget/BlitToTarget.usf", "BlitToTarget", SF_Compute);

void FBlitToTargetInterface::DispatchRenderThread(FRHICommandListImmediate& RHICmdList, FBlitToTargetDispatchParams Params) {
	FRDGBuilder GraphBuilder(RHICmdList);

	{
		SCOPE_CYCLE_COUNTER(STAT_BlitToTarget_Execute);
		DECLARE_GPU_STAT(BlitToTarget)
		RDG_EVENT_SCOPE(GraphBuilder, "BlitToTarget");
		RDG_GPU_STAT_SCOPE(GraphBuilder, BlitToTarget);

		TShaderMapRef<FBlitToTarget> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
		

		bool bIsShaderValid = ComputeShader.IsValid();

		if (bIsShaderValid) {
			FBlitToTarget::FParameters* BackgroundBlitParam = GraphBuilder.AllocParameters<FBlitToTarget::FParameters>();

			
			FRDGTextureDesc Desc(FRDGTextureDesc::Create2D(Params.RenderTarget->GetSizeXY(), PF_B8G8R8A8, FClearValueBinding::White, TexCreate_RenderTargetable | TexCreate_ShaderResource | TexCreate_UAV));
			FRDGTextureRef TmpTexture = GraphBuilder.CreateTexture(Desc, TEXT("BlitToTarget_TempTexture"));
			FRDGTextureRef TargetTexture = RegisterExternalTexture(GraphBuilder, Params.RenderTarget->GetRenderTargetTexture(), TEXT("BlitToTarget_RT"));
			BackgroundBlitParam->RenderTarget = GraphBuilder.CreateUAV(TmpTexture);
			FRDGTextureRef InputTexture = RegisterExternalTexture(GraphBuilder,Params.BackgroundTexture->GetTextureRHI(),TEXT("BlitToTarget_Inpute"));
			BackgroundBlitParam->InputTexture = GraphBuilder.CreateSRV(InputTexture);

			auto GroupCount = FComputeShaderUtils::GetGroupCount(FIntVector(Params.X, Params.Y, Params.Z), FComputeShaderUtils::kGolden2DGroupSize);
			GraphBuilder.AddPass(
				RDG_EVENT_NAME("ExecuteBlitToTarget"),
				BackgroundBlitParam,
				ERDGPassFlags::AsyncCompute,
				[&BackgroundBlitParam, ComputeShader, GroupCount](FRHIComputeCommandList& RHICmdList)
			{
				FComputeShaderUtils::Dispatch(RHICmdList, ComputeShader, *BackgroundBlitParam, GroupCount);
			});

			
			// The copy will fail if we don't have matching formats, let's check and make sure we do.
			if (TargetTexture->Desc.Format == PF_B8G8R8A8) {
				AddCopyTexturePass(GraphBuilder, TmpTexture, TargetTexture, FRHICopyTextureInfo());
			} else {
				#if WITH_EDITOR
					GEngine->AddOnScreenDebugMessage((uint64)42145125184, 6.f, FColor::Red, FString(TEXT("The provided render target has an incompatible format (Please change the RT format to: RGBA8).")));
				#endif
			}
			
		} else {
			#if WITH_EDITOR
				GEngine->AddOnScreenDebugMessage((uint64)42145125184, 6.f, FColor::Red, FString(TEXT("The compute shader has a problem.")));
			#endif

			// We exit here as we don't want to crash the game if the shader is not found or has an error.
			
		}
	}

	GraphBuilder.Execute();
}