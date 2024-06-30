#include "GP3_Team09/Public/AudioManager.h"
#include "Kismet/GameplayStatics.h"

AAudioManager::AAudioManager()
{
	
}

void AAudioManager::BeginPlay()
{
	/*
	if (ensure(SoundToPlay && GetOwner()))
	{
		UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, GetActorLocation());
	}
	*/
}

void AAudioManager::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	
}

void AAudioManager::PlaySoundFromActor(FString Key, AActor* CameFrom)
{
	if (AudioClips.Contains(Key) && CameFrom)
	{
		UGameplayStatics::PlaySoundAtLocation(this, AudioClips[Key], CameFrom->GetActorLocation());
	}
}

void AAudioManager::PlaySound(FString Key)
{
	if (AudioClips.Contains(Key))
	{
		UGameplayStatics::PlaySound2D(this, AudioClips[Key]);
	}
}