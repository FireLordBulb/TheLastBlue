#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SpiritAIStates.h"
#include "BTTask_SetSpiritState.generated.h"

UCLASS()
class UBTTask_SetSpiritState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	explicit UBTTask_SetSpiritState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "State", meta = (AllowPrivateAccess = "true"))
	ESpiritState State;
};
