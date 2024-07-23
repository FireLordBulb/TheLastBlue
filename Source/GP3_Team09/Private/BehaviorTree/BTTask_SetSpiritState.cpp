#include "BehaviorTree/BTTask_SetSpiritState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpiritAIController.h"
#include "SpiritPawn.h"
#include "Kismet/GameplayStatics.h"

UBTTask_SetSpiritState::UBTTask_SetSpiritState() : UBTTask_BlackboardBase()
{
	NodeName = "Set Spirit State";
}

EBTNodeResult::Type UBTTask_SetSpiritState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// get the blackboard component
	if (auto* const Blackboard = OwnerComp.GetBlackboardComponent())
	{
		ASpiritPawn* Spirit = Cast<ASpiritPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpiritPawn::StaticClass()));
		if (Spirit)
		{
			ASpiritAIController* Controller = Cast<ASpiritAIController>(Spirit->GetController());
			if(Controller)
			{
				Controller->SetAIState(State);
			}
		}
		Blackboard->SetValueAsEnum("State", static_cast<uint8>(State));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
