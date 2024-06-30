// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JournalWordTypes.generated.h"

USTRUCT(BlueprintType)
struct FUTranslatedWord
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentTranslationIndex = -1;
};

UCLASS()
class GP3_TEAM09_API UJournalWordTypes : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="Words", meta=(AllowPrivateAccess = true))
	void SetWordIndex(FString Key, int NewIndex);

	UFUNCTION(BlueprintCallable,BlueprintPure, Category="Words", meta=(AllowPrivateAccess = true))
	int GetWordIndex(FString Key) const;

	UFUNCTION(BlueprintCallable)
	void ClearWords();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Words", meta=(AllowPrivateAccess = true))
	TMap<FString, FUTranslatedWord> ObtainedWords;
};
