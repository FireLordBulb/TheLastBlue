#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/MaterialRenderProxy.h"

#include "BlitToTarget.generated.h"


struct FSentence;

struct GLYPHCOMPUTE_API FBlitToTargetDispatchParams
{
	int X;
	int Y;
	int Z;

	FTexture* BackgroundTexture;
	FSentence* SentenceData;
	FRenderTarget* RenderTarget;
	
	

	FBlitToTargetDispatchParams(int x, int y, int z)
		: X(x)
		, Y(y)
		, Z(z)
	{
	}
};

// This is a public interface that we define so outside code can invoke our compute shader.
class GLYPHCOMPUTE_API FBlitToTargetInterface {
public:
	// Executes this shader on the render thread
	static void DispatchRenderThread(
		FRHICommandListImmediate& RHICmdList,
		FBlitToTargetDispatchParams Params
	);

	// Executes this shader on the render thread from the game thread via EnqueueRenderThreadCommand
	static void DispatchGameThread(
		FBlitToTargetDispatchParams Params
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
		FBlitToTargetDispatchParams Params
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
class GLYPHCOMPUTE_API UBlitToTargetLibrary : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static void ExecuteBlitToTargetComputeShader(UTextureRenderTarget2D* RT, UTexture2D* Input)
	{
		// Create a dispatch parameters struct and fill it the input array with our args
		FBlitToTargetDispatchParams Params(RT->SizeX, RT->SizeY, 1);
		Params.RenderTarget = RT->GameThread_GetRenderTargetResource();
		Params.BackgroundTexture = Input->GetResource();
		FBlitToTargetInterface::Dispatch(Params);
	}
};
