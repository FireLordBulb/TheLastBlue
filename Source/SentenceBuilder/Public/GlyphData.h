#pragma once
#include "GlyphData.generated.h"
USTRUCT(BlueprintType)
struct FGlyphData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Glyphs)
	FString Meaning;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Glyphs)
	UTexture2D* Texture;
};
