#include "Proposition.h"
#include "GlyphPosition.h"
bool FProposition::SetGlyph(EGlyphPosition Position,const FGlyphData& NewGlyph)
{
	if(NewGlyph.Texture == nullptr)return false;//means something went wrong
	switch (Position) {//I could avoid this by making the struct an array and have the slot be implicit, but it is error-prone
	case Major:
		MajorGlyph = NewGlyph;
		break;
	case Subject:
		SubjectGlyph = NewGlyph;
		break;
	case SubAdjective:
		SubjectAdjectiveGlyph = NewGlyph;
		break;
	case Verb:
		VerbGlyph = NewGlyph;
		break;
	case Adverb:
		AdverbGlyph = NewGlyph;
		break;
	case Object:
		ObjectGlyph = NewGlyph;
		break;
	case ObjAdjective:
		ObjectAdjectiveGlyph = NewGlyph;
		break;
	case Past:
		PastGlyph = NewGlyph;
		break;
	case Future:
		FutureGlyph = NewGlyph;
		break;
	case Central:
		CentralGlyph = NewGlyph;
		break;
	case Conjunction:
		ConjunctionVerbData = NewGlyph;
		break;
	default:
		UE_LOG(LogTemp,Error,TEXT("Tried to retrieve a non existant glyph type, did you extend the proposition class ?"));
		return false;
	}
	return true;
}
