#include "SentencesGuesser.h"

bool USentencesGuesser::IsCorrectGuess(FString Key, FString Guess)
{
	if (AvailableGuesses.Contains(Key) && Key.Equals(Guess, ESearchCase::IgnoreCase))
	{
		return true;
	}
	return false;
}

void USentencesGuesser::CheckKeys()
{
	for (auto Word : AvailableGuesses)
	{
		if(!Word.Value.Guesses.Contains(Word.Key))
			UE_LOG(LogTemp, Error, TEXT("ERROR in SentenceGuesser on key \"%s\" no guess matches the key"), *Word.Key);
	}
}
