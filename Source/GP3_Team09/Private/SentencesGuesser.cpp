#include "SentencesGuesser.h"

void FUGuesses::FindKey(FString Key)
{
	for (FString Guess : Guesses)
	{
		if (Guess.Equals(Key, ESearchCase::IgnoreCase))
		{
			CorrectGuess = Key;
			return;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("ERROR in SentenceGuesser on key \"%s\" no guess matches the key"), *Key);
}

void USentencesGuesser::BeginPlay()
{
	for (auto Word : AvailableGuesses)
	{
		Word.Value.FindKey(Word.Key);
	}
}
