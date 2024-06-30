#include "BehaviorTree/BTService_CheckPlayerDistance.h"
#include "SpiritAIController.h"
#include "SpiritPawn.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpiritAIStates.h"

UBTService_CheckPlayerDistance::UBTService_CheckPlayerDistance() : UBTService_BlackboardBase()
{
	NodeName = "Check Player Distance";
}

void UBTService_CheckPlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// get the spirit AI controller
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		// get the spirit AI
		if (auto* const Spirit = Cast<ASpiritPawn>(Controller->GetPawn()))
		{
			// get the blackboard component
			if (auto* const Blackboard = OwnerComp.GetBlackboardComponent())
			{
				// get player
				if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
				{
					float Distance = FVector::Dist(Spirit->GetActorLocation(), Player->GetActorLocation());

					bool bIsOutOfRange = (Distance > MaxDistanceThreshold);
					bool bIsInRange = (Distance <= MinDistanceThreshold);
					
					bool bIsInTalkingRange = (Distance <= TalkDistanceThreshold);
					
					bool bStartSprinting = (Distance > MaxWalkThreshold);
					bool bStopSprinting = (Distance <= MinWalkThreshold);

					//Checks if player is faster than spirit, will catch up to the player
					if (bStartSprinting)
					{
						if (Controller->SpiritStateManager->GetCurrentStage() != ESpiritLevelStage::StageTwo)
						{
							Controller->SpiritStateManager->SetMovementSpeed(ESpiritMovementSpeed::Fast);
						}
					}
					if (bStopSprinting)
					{
						if (Controller->SpiritStateManager->GetCurrentStage() != ESpiritLevelStage::StageTwo)
						{
							Controller->SpiritStateManager->SetMovementSpeed(ESpiritMovementSpeed::Normal);
						}
					}

					// Checks if player is too far away, will wait for player
					if (bIsOutOfRange && Controller->SpiritStateManager->GetCurrentState() != ESpiritState::Follow)
					{
						Controller->SetAIState(ESpiritState::OutOfRange);
						Blackboard->SetValueAsEnum("State", static_cast<uint8>(ESpiritState::OutOfRange));
											}
					if (bIsInRange && Controller->SpiritStateManager->GetCurrentState() == ESpiritState::OutOfRange)
					{
						Controller->SetAIState(Controller->SpiritStateManager->GetPreviousState());
						Blackboard->SetValueAsEnum("State", static_cast<uint8>(Controller->SpiritStateManager->GetCurrentState()));
					}
					
					// Checks if player is in range to start talk
					if (!bIsInTalkingRange && Controller->SpiritStateManager->GetCurrentState() == ESpiritState::Talk)
					{
						Blackboard->SetValueAsBool("InRangeToTalk", false);
					}
					if (bIsInTalkingRange && Controller->SpiritStateManager->GetCurrentState() == ESpiritState::Talk)
					{
						Blackboard->SetValueAsBool("InRangeToTalk", true);
					}

				}
			}
		}
	}
}
