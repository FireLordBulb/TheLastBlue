#include "BehaviorTree/BTTask_GetRandomLocation.h"
#include "SpiritAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetRandomLocation::UBTTask_GetRandomLocation() : UBTTask_BlackboardBase()
{
	NodeName = "Get Random Location Around Player";
}

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get AI controller
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		// get player
		if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			// use player location as origin
			auto const Origin = Player->GetActorLocation();

			// get navigation system
			if (auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Location;
				// get random location
				if (NavSys->GetRandomPointInNavigableRadius(Origin, Radius, Location))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(
						GetSelectedBlackboardKey(),
						Location.Location
					);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
