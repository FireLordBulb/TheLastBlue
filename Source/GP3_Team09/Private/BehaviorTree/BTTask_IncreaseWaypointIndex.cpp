#include "BehaviorTree/BTTask_IncreaseWaypointIndex.h"
#include "SpiritAIController.h"
#include "SpiritPawn.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_IncreaseWaypointIndex::UBTTask_IncreaseWaypointIndex() : UBTTask_BlackboardBase()
{
	NodeName = "Increase Waypoint Index";
}

EBTNodeResult::Type UBTTask_IncreaseWaypointIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get the spirit AI controller
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		// get the spirit AI
		if (auto* const Spirit = Cast<ASpiritPawn>(Controller->GetPawn()))
		{
			// get the blackboard component
			if (auto* const Blackboard = OwnerComp.GetBlackboardComponent())
			{
				// get the number of waypoints and index of current waypoint
				auto const NumOfPoints = Spirit->GetWaypointPath()->Num();
				auto Index = Blackboard->GetValueAsInt(GetSelectedBlackboardKey());

				// Fail Task when final waypoint is reached
				if (Index >= NumOfPoints - 1)
				{
					return EBTNodeResult::Failed;
				}

				// increase index to next waypoint
				Blackboard->SetValueAsInt(GetSelectedBlackboardKey(), ++Index);

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
