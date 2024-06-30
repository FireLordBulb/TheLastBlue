#pragma once
#include "Proposition.h"
#include "Sentence.generated.h"

USTRUCT(BlueprintType)
struct FSentence//This is intended to be a transient type and you should rarely serialize it directly
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FProposition> Propositions;
	TArray<UTexture2D*> GetOrderedTextureArray() const;
};
