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
};

UCLASS()
class GP3_TEAM09_API USentencesGuesser : public UPrimaryDataAsset
{
	GENERATED_BODY()

	private:
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Guesses", meta=(AllowPrivateAccess = true))
		TMap<FString, FUGuesses> AvailableGuesses;

		UFUNCTION(BlueprintCallable)
		bool IsCorrectGuess(FString Key, FString Guess);
		
		UFUNCTION(BlueprintCallable)
		void CheckKeys();
};
