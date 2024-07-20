#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "InteractionWidget.generated.h"

UCLASS()
class GP3_TEAM09_API UInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void DisableSpiritImage();
	void DisableInteractionImage();
	void ChangeInteractionIcon(bool IsPuzzle);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* PuzzleImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* MuralImage;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* InteractionImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* SpiritTalkImage;
};