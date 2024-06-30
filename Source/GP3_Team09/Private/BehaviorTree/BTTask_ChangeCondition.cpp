#include "BehaviorTree/BTTask_ChangeCondition.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ChangeCondition::UBTTask_ChangeCondition() : UBTTask_BlackboardBase()
{
	NodeName = "Change Condition";
}

EBTNodeResult::Type UBTTask_ChangeCondition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get the blackboard component
	if (auto* const Blackboard = OwnerComp.GetBlackboardComponent())
	{
		bool Condition = SetCondition;
		Blackboard->SetValueAsBool(GetSelectedBlackboardKey(), Condition);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
