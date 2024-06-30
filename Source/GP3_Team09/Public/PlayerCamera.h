#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "PlayerCamera.generated.h"

UCLASS()
class GP3_TEAM09_API UPlayerCamera : public UCameraComponent
{
	GENERATED_BODY()

	UPlayerCamera();

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
