#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "NavLinkSpirit.generated.h"

UCLASS()
class ANavLinkSpirit : public ANavLinkProxy
{
	GENERATED_BODY()
	
public:
	ANavLinkSpirit();

protected:
	UFUNCTION(BlueprintCallable)
	void HandleJump(AActor* Agent, const FVector& Destination);
};
