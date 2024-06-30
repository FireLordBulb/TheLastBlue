#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESpiritState : uint8
{
	Follow UMETA(DisplayName = "Follow"),
	Explore UMETA(DisplayName = "Explore"),
	Waypoint UMETA(DisplayName = "Waypoint"),
	Talk UMETA(DisplayName = "Talk"),
	Wait UMETA(DisplayName = "Wait"),
	OutOfRange UMETA(DisplayName = "Out of Range"),
	ShowGlyph UMETA(DisplayName = "ShowGlyph")
};

UENUM(BlueprintType)
enum class ESpiritMovementSpeed : uint8
{
	Slow UMETA(DisplayName = "Slow"),
	Normal UMETA(DisplayName = "Normal"),
	Fast UMETA(DisplayName = "Fast")
};

UENUM(BlueprintType)
enum class ESpiritLevelStage :uint8
{
	StageOne UMETA(DisplayName = "StageOne"),
	StageTwo UMETA(DisplayName = "StageTwo"),
	StageThree UMETA(DisplayName = "StageThree")
};