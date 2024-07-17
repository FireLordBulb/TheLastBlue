#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SentencesGuesser.generated.h"

USTRUCT(BlueprintType)
struct FUGuesses
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> Guesses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString CorrectGuess;
	
	void FindKey(FString Key);
};

UCLASS()
class GP3_TEAM09_API USentencesGuesser : public UPrimaryDataAsset
{
	GENERATED_BODY()

	private:
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Guesses", meta=(AllowPrivateAccess = true))
		TMap<FString, FUGuesses> AvailableGuesses;

		UFUNCTION(BlueprintCallable)
		void BeginPlay();
};
