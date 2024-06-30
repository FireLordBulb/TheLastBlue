#include "SpiritDialogueWidget.h"
#include "Glyph.h"
#include "SubGlyph.h"
#include "Components/Image.h"
#include "Engine/TextureRenderTarget2D.h"

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
