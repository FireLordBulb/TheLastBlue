#include "InteractionWidget.h"
#include "Components/Image.h"

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInteractionWidget::ChangeInteractionIcon(bool IsPuzzle)
{
	if (IsPuzzle)
	{
		InteractionImage->SetBrushFromTexture(PuzzleImage);
	}
	else
	{
		InteractionImage->SetBrushFromTexture(MuralImage);
	}
}

void UInteractionWidget::DisableSpiritImage()
{
	SpiritTalkImage->SetVisibility(ESlateVisibility::Hidden);
}

void UInteractionWidget::DisableInteractionImage()
{
	InteractionImage->SetVisibility(ESlateVisibility::Hidden);
}

