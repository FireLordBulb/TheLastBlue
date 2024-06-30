// Fill out your copyright notice in the Description page of Project Settings.


#include "GlyphLibrary.h"
#include "GlyphData.h"

void UGlyphLibrary::GetGlyphData(const FString& word, FGlyphData& glyph, bool& success)
{
	if(!Dictionary.Contains(word))
	{
		success = false;
		glyph = FGlyphData {
			word,
			nullptr
		};
		return;
	}
	glyph = FGlyphData {
		word,
		Dictionary[word]
	};
	success = true;
}
