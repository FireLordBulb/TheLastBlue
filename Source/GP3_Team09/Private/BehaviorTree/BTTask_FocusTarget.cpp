#include "BehaviorTree/BTTask_FocusTarget.h"
#include "SpiritAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FocusTarget::UBTTask_FocusTarget() : UBTTask_BlackboardBase()
{
	NodeName = "Focus Target";
}

EBTNodeResult::Type UBTTask_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get the spirit AI controller
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		// get the blackboard component
		if (auto* const Blackboard = OwnerComp.GetBlackboardComponent())
		{
			auto Focus = Blackboard->GetValueAsObject(FocusTargetKey.SelectedKeyName);

			if (auto* FocusTarget = Cast<AActor>(Focus))
			{
				Controller->SetFocus(FocusTarget);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
