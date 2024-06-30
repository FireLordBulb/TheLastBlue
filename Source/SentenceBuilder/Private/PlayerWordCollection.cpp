// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWordCollection.h"

#include "GlyphPosition.h"
#include "PlainSentence.h"

void UPlayerWordCollection::AddWord(const FString& word, TSet<FString>& set)
{
	//I could return the result but I don't see what we would use it for now
	if (!word.IsEmpty())
	{
		bool added = true;
		if (set.Contains(word))
		{
			added = false;
		}
		set.Add(word);
		OnWordAdded.Broadcast(word, set, added);
	}
}

TSet<FString> UPlayerWordCollection::GetMajorWords() const
{
	return Majors;
}

TSet<FString> UPlayerWordCollection::GetNouns() const
{
	return Nouns;
}

TSet<FString> UPlayerWordCollection::GetVerbs() const
{
	return Verbs;
}

TSet<FString> UPlayerWordCollection::GetAdverbs() const
{
	return Adverbs;
}

TSet<FString> UPlayerWordCollection::GetAdjectives() const
{
	return Adjectives;
}

TSet<FString> UPlayerWordCollection::GetTenses() const
{
	return Tenses;
}

TSet<FString> UPlayerWordCollection::GetConjunctions() const
{
	return Conjunctions;
}

TSet<FString> UPlayerWordCollection::GetCentral() const
{
	return Central;
}

void UPlayerWordCollection::ClearAllWords()
{
	Majors.Empty();
	Nouns.Empty();
	Verbs.Empty();
	Adjectives.Empty();
}

void UPlayerWordCollection::AddMissingWordsFromSentence(const FPlainSentence& Sentence)
{
	//It might be nice to check the words against the libraries here
	for (auto proposition : Sentence.Propositions)
	{
		//really need a proposition iterator
		AddWord(proposition.Case,Majors);
		AddWord(proposition.Subject,Nouns);
		AddWord(proposition.SubjectAdjective,Adjectives);
		AddWord(proposition.Verb,Verbs);
		AddWord(proposition.Adverb,Adverbs);
		AddWord(proposition.Object,Nouns);
		AddWord(proposition.ObjectAdjective,Adjectives);
		AddWord(proposition.Past,Tenses);
		AddWord(proposition.Future, Tenses);
		AddWord(proposition.Central,Central);
		AddWord(proposition.Conjunction,Conjunctions);
	}
}

const TSet<FString>& UPlayerWordCollection::GetKnownWords(EGlyphPosition Position) const 
{
	switch (Position) {
	case Major:
		return Majors;
	case Subject:
	case Object:
		return Nouns;
	case SubAdjective:
	case ObjAdjective:
		return Adjectives;
	case Verb:
		return Verbs;
	case Adverb:
		return Adverbs;
	case Past:
	case Future:
		return Tenses;
	case EGlyphPosition::Central:
		return Central;
	case Conjunction:
		return Conjunctions;
	case None://should never happen
		default:
		return Majors;
	}
}

bool UPlayerWordCollection::ContainsWord(EGlyphPosition position, FString word) const
{
	return GetKnownWords(position).Contains(word);
}
