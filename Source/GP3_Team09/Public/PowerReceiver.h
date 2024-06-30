#pragma once
#include "PowerReceiver.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UPowerReceiver : public UInterface
{
	GENERATED_BODY()
};

class IPowerReceiver
{    
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPowerOn();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPowerOff();
 
	// Unreal doesn't let me use UGlyphProvider* as the return type. AAAAAUUGGHH!
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UActorComponent* GetGlyphProvider();
};