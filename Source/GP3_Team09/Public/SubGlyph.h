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
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class USubGlyph : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USubGlyph();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	/** Determines whether or not the player can interact with this SubGlyph to change it. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsEditable = true;
	/** Array of possible symbols this SubGlyph can be swapped to. Always loads the Symbol at index 0 on game start, regardless of the value of IsEditable. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSubGlyphSymbol> Symbols;
	UPROPERTY(BlueprintReadWrite)
	int CurrentSymbolIndex = 0;
	UPROPERTY(BlueprintReadWrite)
	UMeshComponent* TempMesh;
	
};
