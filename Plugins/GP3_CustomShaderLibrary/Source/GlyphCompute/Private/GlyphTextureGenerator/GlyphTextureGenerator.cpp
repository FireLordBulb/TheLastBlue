#include "GlyphTextureGenerator.h"
#include "GlyphCompute/Public/GlyphTextureGenerator/GlyphTextureGenerator.h"

#include <string>

#include "PixelShaderUtils.h"
#include "MeshPassProcessor.inl"
#include "StaticMeshResources.h"
#include "DynamicMeshBuilder.h"
#include "RenderGraphResources.h"
#include "GlobalShader.h"
#include "HLSLTypeAliases.h"
#include "UnifiedBuffer.h"

DECLARE_STATS_GROUP(TEXT("GlyphTextureGenerator"), STATGROUP_GlyphTextureGenerator, STATCAT_Advanced);
DECLARE_CYCLE_STAT(TEXT("GlyphTextureGenerator Execute"), STAT_GlyphTextureGenerator_Execute, STATGROUP_GlyphTextureGenerator);

// This class carries our parameter declarations and acts as the bridge between cpp and HLSL.
class GLYPHCOMPUTE_API FGlyphTextureGenerator: public FGlobalShader
{
public:
	
	DECLARE_GLOBAL_SHADER(FGlyphTextureGenerator);
	SHADER_USE_PARAMETER_STRUCT(FGlyphTextureGenerator, FGlobalShader);
	
	
	class FGlyphTextureGenerator_Perm_TEST : SHADER_PERMUTATION_INT("TEST", 1);
	using FPermutationDomain = TShaderPermutationDomain<
		FGlyphTextureGenerator_Perm_TEST
	>;

	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		/*
		* Here's where you define one or more of the input parameters for your shader.
		* Some examples:
		*/
		// SHADER_PARAMETER(uint32, MyUint32) // On the shader side: uint32 MyUint32;
		SHADER_PARAMETER(UE::HLSL::uint2, offset) // On the shader side: float3 MyVector;
		SHADER_PARAMETER(UE::HLSL::uint2, mask)
		// SHADER_PARAMETER_TEXTURE(Texture2D, MyTexture) // On the shader side: Texture2D<float4> MyTexture; (float4 should be whatever you expect each pixel in the texture to be, in this case float4(R,G,B,A) for 4 channels)
		// SHADER_PARAMETER_SAMPLER(SamplerState, MyTextureSampler) // On the shader side: SamplerState MySampler; // CPP side: TStaticSamplerState<ESamplerFilter::SF_Bilinear>::GetRHI();

		// SHADER_PARAMETER_ARRAY(float, MyFloatArray, [3]) // On the shader side: float MyFloatArray[3];

		// SHADER_PARAMETER_UAV(RWTexture2D<FVector4f>, MyTextureUAV) // On the shader side: RWTexture2D<float4> MyTextureUAV;
		// SHADER_PARAMETER_UAV(RWStructuredBuffer<FMyCustomStruct>, MyCustomStructs) // On the shader side: RWStructuredBuffer<FMyCustomStruct> MyCustomStructs;
		// SHADER_PARAMETER_UAV(RWBuffer<FMyCustomStruct>, MyCustomStructs) // On the shader side: RWBuffer<FMyCustomStruct> MyCustomStructs;

		// SHADER_PARAMETER_SRV(StructuredBuffer<FMyCustomStruct>, MyCustomStructs) // On the shader side: StructuredBuffer<FMyCustomStruct> MyCustomStructs;
		// SHADER_PARAMETER_SRV(Buffer<FMyCustomStruct>, MyCustomStructs) // On the shader side: Buffer<FMyCustomStruct> MyCustomStructs;
		// SHADER_PARAMETER_SRV(Texture2D<FVector4f>, MyReadOnlyTexture) // On the shader side: Texture2D<float4> MyReadOnlyTexture;

		// SHADER_PARAMETER_STRUCT_REF(FMyCustomStruct, MyCustomStruct)
		
		SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D,InputTexture)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D, RenderTarget)
		
	
		

	END_SHADER_PARAMETER_STRUCT()

public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		const FPermutationDomain PermutationVector(Parameters.PermutationId);
		
		return true;
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);

		const FPermutationDomain PermutationVector(Parameters.PermutationId);

		/*
		* Here you define constants that can be used statically in the shader code.
		* Example:
		*/
		// OutEnvironment.SetDefine(TEXT("MY_CUSTOM_CONST"), TEXT("1"));

		/*
		* These defines are used in the thread count section of our shader
		*/
		OutEnvironment.SetDefine(TEXT("THREADS_X"), NUM_THREADS_GlyphTextureGenerator_X);
		OutEnvironment.SetDefine(TEXT("THREADS_Y"), NUM_THREADS_GlyphTextureGenerator_Y);
		OutEnvironment.SetDefine(TEXT("THREADS_Z"), NUM_THREADS_GlyphTextureGenerator_Z);

		// This shader must support typed UAV load and we are testing if it is supported at runtime using RHIIsTypedUAVLoadSupported
		//OutEnvironment.CompilerFlags.Add(CFLAG_AllowTypedUAVLoads);

		// FForwardLightingParameters::ModifyCompilationEnvironment(Parameters.Platform, OutEnvironment);
	}
private:
};

// This will tell the engine to create the shader and where the shader entry point is.
//                            ShaderType                            ShaderPath                     Shader function name    Type
IMPLEMENT_GLOBAL_SHADER(FGlyphTextureGenerator, "/GlyphComputeShaders/GlyphTextureGenerator/GlyphTextureGenerator.usf", "GlyphTextureGenerator", SF_Compute);

void FGlyphTextureGeneratorInterface::DispatchRenderThread(FRHICommandListImmediate& RHICmdList, FGlyphTextureGeneratorDispatchParams Params) {
	FRDGBuilder GraphBuilder(RHICmdList);
	TArray<FGlyphTextureGenerator::FParameters*> paramArray = TArray<FGlyphTextureGenerator::FParameters*>();
	{
		SCOPE_CYCLE_COUNTER(STAT_GlyphTextureGenerator_Execute);
		DECLARE_GPU_STAT(GlyphTextureGenerator)
		RDG_EVENT_SCOPE(GraphBuilder, "GlyphTextureGenerator");
		RDG_GPU_STAT_SCOPE(GraphBuilder, GlyphTextureGenerator);
		
		typename FGlyphTextureGenerator::FPermutationDomain PermutationVector;
		
		// Add any static permutation options here
		// PermutationVector.Set<FGlyphTextureGenerator::FMyPermutationName>(12345);

		TShaderMapRef<FGlyphTextureGenerator> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel), PermutationVector);
		
		bool bIsShaderValid = ComputeShader.IsValid();

		if (bIsShaderValid) {
			FIntPoint RenderTargetSize = Params.RenderTarget->GetSizeXY();
			FRDGTextureDesc Desc(FRDGTextureDesc::Create2D(RenderTargetSize, PF_B8G8R8A8, FClearValueBinding::Transparent, TexCreate_RenderTargetable | TexCreate_ShaderResource | TexCreate_UAV));
			FRDGTextureRef TmpTexture = GraphBuilder.CreateTexture(Desc, TEXT("GlyphTextureGenerator_TempTexture"));
			FRDGTextureRef TargetTexture = RegisterExternalTexture(GraphBuilder, Params.RenderTarget->GetRenderTargetTexture(), TEXT("GlyphTextureGenerator_RT"));
 			FRDGTextureUAVRef targetUAV = GraphBuilder.CreateUAV(TmpTexture);
			
			
			AddClearUAVPass(GraphBuilder,targetUAV,FLinearColor::Transparent);
			ensure(Params.Textures.Num() == Params.Offsets.Num());
			for(int i = 0; i < Params.Textures.Num();i++)
			{
				if(Params.Textures[i] == nullptr || Params.Textures[i]->IsDefaultSubobject())
				{
					paramArray.Add(nullptr);
					continue;
				}
				FGlyphTextureGenerator::FParameters* PassParam = GraphBuilder.AllocParameters<FGlyphTextureGenerator::FParameters>();
				PassParam->RenderTarget = targetUAV;
				
				FRDGTextureRef GlyphTexture = RegisterExternalTexture(GraphBuilder,Params.Textures[i]->GetResource()->GetTextureRHI(),*FString::Printf(TEXT("GTGTexture%d"),i));
				PassParam->InputTexture = GraphBuilder.CreateSRV(GlyphTexture);
				auto inputSize = GlyphTexture->Desc.GetSize();
				PassParam->offset.X = FMath::RoundToInt(RenderTargetSize.X * Params.Offsets[i].X) - inputSize.X/2;
				PassParam->offset.Y = FMath::RoundToInt(RenderTargetSize.Y * Params.Offsets[i].Y) - inputSize.Y/2;
				PassParam->mask = UE::HLSL::uint2(Params.masks[i]);//probably ok
				auto GroupCount = FComputeShaderUtils::GetGroupCount(FIntVector(inputSize.X/4, inputSize.Y/4, 1), FComputeShaderUtils::kGolden2DGroupSize);
				paramArray.Add(PassParam);
				GraphBuilder.AddPass(
					RDG_EVENT_NAME("ExecuteGlyphTextureGenerator%d", i),
					paramArray[i],
					ERDGPassFlags::AsyncCompute,
					[&paramArray, i, ComputeShader, GroupCount](FRHIComputeCommandList& RHICmdList)
				{
					FComputeShaderUtils::Dispatch(RHICmdList, ComputeShader, *paramArray[i], GroupCount);
				});
			}
			

			
			// The copy will fail if we don't have matching formats, let's check and make sure we do.
			if (TargetTexture->Desc.Format == RTF_RGBA8 || TargetTexture->Desc.Format == GetPixelFormatFromRenderTargetFormat(RTF_RGBA8)) {
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
