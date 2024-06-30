#pragma once
#include "GlyphPosition.h"
#include "PlainProposition.generated.h"
USTRUCT(BlueprintType)
struct FPlainProposition
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Case = "Statement";
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Subject;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString SubjectAdjective;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Verb;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Adverb;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Object;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ObjectAdjective;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Past;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Future;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Central;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Conjunction;
	
	bool SetWord(EGlyphPosition Position, const FString& Word);
	friend bool operator==(const FPlainProposition& l,const FPlainProposition& r)
	{
		if(l.Case != r.Case)return false;
		if(l.Subject != r.Subject)return false;
		if(l.SubjectAdjective != r.SubjectAdjective)return false;
		if(l.Verb != r.Verb)return false;
		if(l.Adverb != r.Adverb)return false;
		if(l.Object != r.Object)return false;
		if(l.ObjectAdjective != r.ObjectAdjective)return false;
		if(l.Past != r.Past)return false;
		if(l.Future != r.Future)return false;
		if(l.Central != r.Central)return false;
		if(l.Conjunction != r.Conjunction)return false;
		return true;
	}
	friend uint32 GetTypeHash(const FPlainProposition& This)
	{
		uint32 hash = GetTypeHash(This.Case);
		hash = HashCombine(hash,GetTypeHash(This.Subject));
		hash = HashCombine(hash,GetTypeHash(This.Verb));
		hash = HashCombine(hash,GetTypeHash(This.Adverb));
		hash = HashCombine(hash,GetTypeHash(This.SubjectAdjective));
		hash = HashCombine(hash,GetTypeHash(This.Object));
		hash = HashCombine(hash,GetTypeHash(This.ObjectAdjective));
		hash = HashCombine(hash,GetTypeHash(This.Past));
		hash = HashCombine(hash,GetTypeHash(This.Future));
		hash = HashCombine(hash,GetTypeHash(This.Central));
		hash = HashCombine(hash,GetTypeHash(This.Conjunction));
		return hash;
	}
};

inline bool FPlainProposition::SetWord(EGlyphPosition Position, const FString& Word)
{
	switch (Position) {
	case Major:
		Case = Word;
		break;
	case EGlyphPosition::Subject:
		Subject  = Word;
		break;
	case SubAdjective:
		SubjectAdjective = Word;
		break;
	case EGlyphPosition::Verb:
		Verb = Word;
		break;
	case EGlyphPosition::Adverb:
		Adverb = Word;
		break;
	case EGlyphPosition::Object:
		Object = Word;
		break;
	case ObjAdjective:
		ObjectAdjective = Word;
		break;
	case EGlyphPosition::Past:
		Past  = Word;
		break;
	case EGlyphPosition::Future:
		Future = Word;
		break;
	case EGlyphPosition::Central:
		Central = Word;
		break;
	case EGlyphPosition::Conjunction:
		Conjunction = Word;
		break;
		default:
			return false;
	}
	return true;
}
