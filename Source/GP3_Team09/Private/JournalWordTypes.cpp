// Fill out your copyright notice in the Description page of Project Settings.


#include "JournalWordTypes.h"

void UJournalWordTypes::SetWordIndex(FString Key, int NewIndex)
{
	if (ObtainedWords.Contains(Key))
	{
		ObtainedWords[Key].CurrentTranslationIndex = NewIndex;
	}
}

int UJournalWordTypes::GetWordIndex(FString Key)const 
{
	if (ObtainedWords.Contains(Key))
	{
		return ObtainedWords[Key].CurrentTranslationIndex;
	}
	return -1;
}

void UJournalWordTypes::ClearWords()
{
	ObtainedWords.Empty();
}
