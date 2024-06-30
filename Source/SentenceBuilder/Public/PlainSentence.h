#pragma once
#include "PlainProposition.h"
#include "PlainSentence.generated.h"

USTRUCT(BlueprintType)
struct FPlainSentence
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FPlainProposition> Propositions = TArray<FPlainProposition>({FPlainProposition()});
	friend bool operator==(const FPlainSentence& l,const FPlainSentence& r)
	{
		if(l.Propositions.Num() != r.Propositions.Num())return false;
		for(int i = 0; i< l.Propositions.Num();i++)
		{
			if(!(l.Propositions[i] == r.Propositions[i]))return false;
		}
		return true;
	}
	friend uint32 GetTypeHash(const FPlainSentence& This)
	{
		if(This.Propositions.Num() == 0)return 0;
		uint32 hash = GetTypeHash(This.Propositions[0]);
		for(int i = 1; i < This.Propositions.Num();i++)
		{
			hash = HashCombine(hash,GetTypeHash(This.Propositions[i]));
		}
		return hash;
	}
};


