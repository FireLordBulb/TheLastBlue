#include "BehaviorTree/BTTask_MoveToFrontOfPlayer.h"
#include "SpiritAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"

UBTTask_MoveToFrontOfPlayer::UBTTask_MoveToFrontOfPlayer() : UBTTask_BlackboardBase()
{
	NodeName = "Move To InFront of Player";
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MoveToFrontOfPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get the spirit AI controller
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		// get the blackboard component
		if (auto* const Blackboard = OwnerComp.GetBlackboardComponent())
		{
			// get player
			if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
			{
				FVector PlayerLocation = Player->GetActorLocation();
				FVector PlayerForward = Player->GetActorForwardVector();

				FVector TargetLocation = PlayerLocation + PlayerForward * DistanceInFront;

				// Move to properties
				FAIMoveRequest MoveRequest;
				MoveRequest.SetGoalLocation(TargetLocation);
				MoveRequest.SetAcceptanceRadius(AcceptableRadius);

				FNavPathSharedPtr NavPath;
				Controller->MoveTo(MoveRequest, &NavPath);
				
				FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
				return EBTNodeResult::InProgress;
			}
		}
	}
	return EBTNodeResult::Failed;
}

void UBTTask_MoveToFrontOfPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// get the spirit AI controller
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		if (Controller->GetPathFollowingComponent()->DidMoveReachGoal())
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
