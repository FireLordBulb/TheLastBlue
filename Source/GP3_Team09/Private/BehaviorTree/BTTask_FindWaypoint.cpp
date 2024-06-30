#include "BehaviorTree/BTTask_FindWaypoint.h"

#include "SpiritAIController.h"
#include "SpiritPawn.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindWaypoint::UBTTask_FindWaypoint() : UBTTask_BlackboardBase()
{
	NodeName = "Find Waypoint";
}

EBTNodeResult::Type UBTTask_FindWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get the spirit AI controller
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		// get the blackboard component
		if (auto* const Blackboard = OwnerComp.GetBlackboardComponent())
		{
			// get the spirit AI
			if (auto* Spirit = Cast<ASpiritPawn>(Controller->GetPawn()))
			{
				if (Spirit->GetWaypointPath()->Num() > 0)
				{
					// get current waypoint index
					auto const Index = Blackboard->GetValueAsInt(GetSelectedBlackboardKey());

					// get the current waypoints local vector
					auto const LocalWaypoint = Spirit->GetWaypointPath()->GetWaypoint(Index);

					// convert local vector to global vector
					auto const GlobalWaypoint = Spirit->GetWaypointPath()->GetActorTransform().TransformPosition(LocalWaypoint);
					Blackboard->SetValueAsVector(WaypointPathVectorKey.SelectedKeyName, GlobalWaypoint);

					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
