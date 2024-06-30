// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GlyphLibrary.generated.h"

/**
 * Wapper around a dictionnary of string/texture
 */
UCLASS()
class SENTENCEBUILDER_API UGlyphLibrary : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	/** get a glyph data struct from an english word string */
	UFUNCTION(BlueprintPure, Category="glyph library")
	void GetGlyphData(const FString& word, FGlyphData& glyph, bool& success);
	/** dictionary that matches english words to textures */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Data")
	TMap<FString,UTexture2D*> Dictionary;

};
