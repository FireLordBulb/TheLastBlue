#pragma once
#include "GlyphData.h"
#include "Proposition.generated.h"

enum EGlyphPosition : int8;

USTRUCT(BlueprintType)
struct FProposition
{
	GENERATED_BODY()
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData MajorGlyph;
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData SubjectGlyph;
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData SubjectAdjectiveGlyph;
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData VerbGlyph;
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData AdverbGlyph;
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData ObjectGlyph;
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData ObjectAdjectiveGlyph;
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData PastGlyph;
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData FutureGlyph;
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData CentralGlyph;
	UPROPERTY(VisibleInstanceOnly)
	FGlyphData ConjunctionVerbData;//this should be allowed to be empty or blank
	bool SetGlyph(EGlyphPosition Position, const FGlyphData& NewGlyph);
};

