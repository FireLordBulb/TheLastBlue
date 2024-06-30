#include "BehaviorTree/BTTask_ClearFocusTarget.h"
#include "SpiritAIController.h"

UBTTask_ClearFocusTarget::UBTTask_ClearFocusTarget() : UBTTask_BlackboardBase()
{
	NodeName = "Clear Focus";
}

EBTNodeResult::Type UBTTask_ClearFocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get the spirit AI controller
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		Controller->ClearFocus(EAIFocusPriority::Gameplay);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
