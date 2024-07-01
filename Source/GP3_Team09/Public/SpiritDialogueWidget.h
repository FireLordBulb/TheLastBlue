#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpiritDialogueWidget.generated.h"

class UInteraction;
class UImage;

UCLASS()
class USpiritDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
		virtual void NativeConstruct() override;
	
		UFUNCTION()
		void EnableGlyph();

		UFUNCTION()
		void DisableGlyph();
	
	protected:
		UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		UImage* GlyphImage;

		UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* Canvas;
};