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

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* SpiritInteractionImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* SpiritTalkImage;
};