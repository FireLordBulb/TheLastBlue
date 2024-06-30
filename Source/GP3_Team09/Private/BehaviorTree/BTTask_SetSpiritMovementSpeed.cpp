#include "BehaviorTree/BTTask_SetSpiritMovementSpeed.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpiritAIController.h"
#include "SpiritPawn.h"

UBTTask_SetSpiritMovementSpeed::UBTTask_SetSpiritMovementSpeed() : UBTTask_BlackboardBase()
{
	NodeName = "SetMovementSpeed";
}

EBTNodeResult::Type UBTTask_SetSpiritMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get the spirit AI controller
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		// get the spirit AI
		if (auto* const Spirit = Cast<ASpiritPawn>(Controller->GetPawn()))
		{
			auto CharacterMovement = Spirit->GetCharacterMovement();

			switch(SpeedType)
			{
			case ESpiritMovementSpeed::Slow:
				MovementSpeed = 150.f;
				break;
			case ESpiritMovementSpeed::Normal:
				MovementSpeed = 300.f;
				break;
			case ESpiritMovementSpeed::Fast:
				MovementSpeed = 500.f;
				break;
			}

			CharacterMovement->MaxWalkSpeed = MovementSpeed;

			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
