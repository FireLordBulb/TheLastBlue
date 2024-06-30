// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerWordCollection.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAddedWord, const FString&, Word, TSet<FString>, Words, bool, Added);

struct FPlainSentence;
enum EGlyphPosition : int8;
/**
 * Container and interfaces for the various word related Data the player is holding
 * You can create a pre-populated one for testing purposes
 */
UCLASS()
class SENTENCEBUILDER_API UPlayerWordCollection : public UPrimaryDataAsset
{
	GENERATED_BODY()

	//Known words
	UPROPERTY(EditInstanceOnly,BlueprintGetter=GetMajorWords)
	TSet<FString> Majors;
	UPROPERTY(EditInstanceOnly,BlueprintGetter=GetNouns)
	TSet<FString> Nouns;
	UPROPERTY(EditInstanceOnly, BlueprintGetter=GetVerbs)
	TSet<FString> Verbs;
	UPROPERTY(EditInstanceOnly, BlueprintGetter=GetAdverbs)
	TSet<FString> Adverbs;
	UPROPERTY(EditInstanceOnly, BlueprintGetter=GetAdjectives)
	TSet<FString> Adjectives;
	UPROPERTY(EditInstanceOnly, BlueprintGetter=GetTenses)
	TSet<FString> Tenses;
	UPROPERTY(EditInstanceOnly, BlueprintGetter=GetConjunctions)
	TSet<FString> Conjunctions;
	UPROPERTY(EditInstanceOnly, BlueprintGetter=GetCentral)
	TSet<FString> Central;
	UFUNCTION()
	void AddWord( const FString& word, TSet<FString>& set);

public:
	UPROPERTY(BlueprintAssignable)
	FAddedWord OnWordAdded;
	UFUNCTION(BlueprintPure)
	TSet<FString> GetMajorWords() const;
	UFUNCTION(BlueprintPure)
	TSet<FString> GetNouns() const;
	UFUNCTION(BlueprintPure)
	TSet<FString> GetVerbs() const;
	UFUNCTION(BlueprintPure)
	TSet<FString> GetAdverbs() const;
	UFUNCTION(BlueprintPure)
	TSet<FString> GetAdjectives() const;
	UFUNCTION(BlueprintPure)
	TSet<FString> GetTenses() const;
	UFUNCTION(BlueprintPure)
	TSet<FString> GetConjunctions() const;
	UFUNCTION(BlueprintPure)
	TSet<FString> GetCentral() const;
	UFUNCTION(BlueprintCallable)
	void ClearAllWords();
	
	UFUNCTION(BlueprintCallable)
	void AddMissingWordsFromSentence(const FPlainSentence& Sentence);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TSet<FString>& GetKnownWords(EGlyphPosition Position)const ;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool ContainsWord(EGlyphPosition position, FString word) const;
};
