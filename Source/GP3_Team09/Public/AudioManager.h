#pragma once
#include "Components/ActorComponent.h"
#include "AudioManager.generated.h"

class USceneComponent;

UCLASS(ClassGroup=("Custom"), meta=(BlueprintSpawnableComponent))
class AAudioManager : public AActor
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable)
		void PlaySoundFromActor(FString Key, AActor* CameFrom);

		UFUNCTION(BlueprintCallable)
		void PlaySound(FString Key);
	
	
	private:
		AAudioManager();
		virtual void BeginPlay() override;
		virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

		UPROPERTY(EditDefaultsOnly)
		TMap<FString, USoundBase*> AudioClips;
};

