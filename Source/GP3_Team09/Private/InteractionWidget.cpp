#include "InteractionWidget.h"
#include "Components/Image.h"

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UInteractionWidget::DisableSpiritImage()
{
	SpiritInteractionImage->SetVisibility(ESlateVisibility::Hidden);
}