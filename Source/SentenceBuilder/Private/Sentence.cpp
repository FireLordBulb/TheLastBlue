#include "Sentence.h"

TArray<UTexture2D*> FSentence::GetOrderedTextureArray() const
{
	TArray<UTexture2D*> result = TArray<UTexture2D*>();
	for (auto prop : Propositions)
	{
		result.Append({
		prop.MajorGlyph.Texture,
		prop.SubjectGlyph.Texture,
		prop.SubjectAdjectiveGlyph.Texture,
		prop.VerbGlyph.Texture,
		prop.AdverbGlyph.Texture,
		prop.ObjectGlyph.Texture,
		prop.ObjectAdjectiveGlyph.Texture,
		prop.PastGlyph.Texture,
		prop.FutureGlyph.Texture,
		prop.CentralGlyph.Texture,
		prop.ConjunctionVerbData.Texture});
	}
	return result;
}
