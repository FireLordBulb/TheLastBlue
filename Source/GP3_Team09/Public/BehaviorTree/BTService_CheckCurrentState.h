#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckCurrentState.generated.h"

UCLASS()
class GP3_TEAM09_API UBTService_CheckCurrentState : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UBTService_CheckCurrentState();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
