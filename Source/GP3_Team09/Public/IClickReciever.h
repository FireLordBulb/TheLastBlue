// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "IClickReciever.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UIClickReciever : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GP3_TEAM09_API IIClickReciever
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnReceiveClickInput();
};
