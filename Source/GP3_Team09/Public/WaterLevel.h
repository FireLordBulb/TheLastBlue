// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaterLevel.generated.h"


UENUM(BlueprintType, meta=(ScriptName="EWaterLevel"))
enum class EWaterLevel : uint8
{
	MaxWater UMETA(DisplayName = "WaterFull"),
	SixtySixFull UMETA(DisplayName = "SixtySixFull"),
	ThirtyThreeFull UMETA(DisplayName = "ThirtyThreeFull"),
	WaterGone UMETA(DisplayName = "WaterGone")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRaise, EWaterLevel, CurrentWaterLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP3_TEAM09_API UWaterLevel : public UActorComponent
{
	GENERATED_BODY()

public:
	UWaterLevel();
	

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	EWaterLevel CurrentWaterLevel;
	
	UPROPERTY(BlueprintAssignable)
	FRaise Raise;

	UFUNCTION(BlueprintCallable)
	void RaiseWater(EWaterLevel Level);
};
