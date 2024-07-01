// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include <GlyphPosition.h>
#include "SubGlyph.generated.h"


UENUM(BlueprintType)
enum class ETempSymbolEnum : uint8
{
	Open,
	Not,
	Fire,
	Door,
	Forest,
	Is,
	Closed
};

USTRUCT(BlueprintType)
struct FSubGlyphSymbol
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture* Texture;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETempSymbolEnum Meaning;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Word;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EGlyphPosition> Position;
};