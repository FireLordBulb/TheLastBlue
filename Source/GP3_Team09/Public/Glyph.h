// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IClickReciever.h"
#include "GameFramework/Actor.h"
#include "Glyph.generated.h"

class USubGlyph;

UCLASS()
class AGlyph : public AActor, public  IIClickReciever
{
	GENERATED_BODY()

public:
	AGlyph();

protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
	virtual void OnReceiveClickInput_Implementation() override;
	
};
