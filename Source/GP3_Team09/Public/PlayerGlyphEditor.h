// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerGlyphEditor.generated.h"

class IIClickReceiver;

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class GP3_TEAM09_API UPlayerGlyphEditor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerGlyphEditor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<IIClickReceiver> Glyph;
	UPROPERTY(BlueprintReadWrite)
	bool bGlyphEditingIsActive;
};
