#include "WaterLevel.h"

UWaterLevel::UWaterLevel()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWaterLevel::BeginPlay()
{
	Super::BeginPlay();
}

void UWaterLevel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWaterLevel::RaiseWater(EWaterLevel Level)
{
	CurrentWaterLevel = Level;
	Raise.Broadcast(Level);
}

