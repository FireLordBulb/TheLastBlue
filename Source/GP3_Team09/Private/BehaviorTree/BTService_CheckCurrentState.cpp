#include "BehaviorTree/BTService_CheckCurrentState.h"
#include "SpiritPawn.h"
#include "SpiritAIController.h"
#include "SpiritAIStates.h"

UBTService_CheckCurrentState::UBTService_CheckCurrentState() : UBTService_BlackboardBase()
{
	NodeName = "Check Current State";
}

void UBTService_CheckCurrentState::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	// get the spirit AI controller
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		// get the spirit AI
		if (auto* const Spirit = Cast<ASpiritPawn>(Controller->GetPawn()))
		{	
			if (Controller->SpiritStateManager->GetCurrentStage() != ESpiritLevelStage::StageTwo)
			{
				if (Controller->SpiritStateManager->GetCurrentState() == ESpiritState::Waypoint)
				{
					Controller->SpiritStateManager->SetMovementSpeed(ESpiritMovementSpeed::Fast);
				}
				if (Controller->SpiritStateManager->GetCurrentState() == ESpiritState::Wait)
				{
					Controller->SpiritStateManager->SetMovementSpeed(ESpiritMovementSpeed::Normal);
				}
			}
		}
	}
}
