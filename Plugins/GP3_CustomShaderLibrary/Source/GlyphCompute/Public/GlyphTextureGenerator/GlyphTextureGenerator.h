#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/MaterialRenderProxy.h"

#include "GlyphTextureGenerator.generated.h"

struct GLYPHCOMPUTE_API FGlyphTextureGeneratorDispatchParams
{
	int X;
	int Y;
	int Z;

	
	FRenderTarget* RenderTarget;
	TArray<UTexture2D*> Textures;
	TArray<FVector2f> Offsets;
	TArray<FUintVector2> masks;
	
	//add proposition offset here
	FGlyphTextureGeneratorDispatchParams(int x, int y, int z)
		: X(x)
		, Y(y)
		, Z(z)
	{
	}
};



// This is a public interface that we define so outside code can invoke our compute shader.
class GLYPHCOMPUTE_API FGlyphTextureGeneratorInterface {
public:
	// Executes this shader on the render thread
	static void DispatchRenderThread(
		FRHICommandListImmediate& RHICmdList,
		FGlyphTextureGeneratorDispatchParams Params
	);

	// Executes this shader on the render thread from the game thread via EnqueueRenderThreadCommand
	static void DispatchGameThread(
		FGlyphTextureGeneratorDispatchParams Params
	)
	{
		ENQUEUE_RENDER_COMMAND(SceneDrawCompletion)(
		[Params](FRHICommandListImmediate& RHICmdList)
		{
			DispatchRenderThread(RHICmdList, Params);
		});
	}

	// Dispatches this shader. Can be called from any thread
	static void Dispatch(
		FGlyphTextureGeneratorDispatchParams Params
	)
	{
		if (IsInRenderingThread()) {
			DispatchRenderThread(GetImmediateCommandList_ForRenderCommand(), Params);
		}else{
			DispatchGameThread(Params);
		}
	}
	
};

// This is a static blueprint library that can be used to invoke our compute shader from blueprints.
UCLASS()
class GLYPHCOMPUTE_API UGlyphTextureGeneratorLibrary : public UObject
{
	GENERATED_BODY()
public:
	static void CreateSentenceTexture(UTextureRenderTarget2D* RenderTarget,const TArray<UTexture2D*>& Textures,const TArray<FVector2f>& offsets, const TArray<FUintVector2>& masks)
	{
		if(RenderTarget == nullptr)return;
		// Create a dispatch parameters struct and fill it the input array with our args
		FGlyphTextureGeneratorDispatchParams Params(RenderTarget->SizeX, RenderTarget->SizeY, 1);
		Params.RenderTarget = RenderTarget->GameThread_GetRenderTargetResource();
		if(Params.RenderTarget == nullptr)return;

		Params.Textures = Textures;
		Params.Offsets = offsets;
		Params.masks = masks;
		FGlyphTextureGeneratorInterface::Dispatch(Params);
	}
};
