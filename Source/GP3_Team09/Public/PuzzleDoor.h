#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleComplete);

UCLASS(meta=(BlueprintSpawnableComponent))
class APuzzleDoor : public AActor
{
	GENERATED_BODY()

	protected:
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsOpen = false;
	
		APuzzleDoor();
		virtual void BeginPlay() override;
	
		UPROPERTY(BlueprintReadWrite)
		FVector DoorStartPosition;
	private:
		UPROPERTY(VisibleAnywhere)
		USceneComponent* Body = nullptr;
};
