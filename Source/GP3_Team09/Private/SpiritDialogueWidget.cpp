#include "SpiritDialogueWidget.h"
#include "Components/Image.h"

void USpiritDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USpiritDialogueWidget::EnableGlyph()
{
	SetVisibility(ESlateVisibility::Visible);
}

void USpiritDialogueWidget::DisableGlyph()
{
	SetVisibility(ESlateVisibility::Hidden);
}
