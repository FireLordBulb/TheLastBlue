#include "PlayerCamera.h"

UPlayerCamera::UPlayerCamera()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCamera::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
