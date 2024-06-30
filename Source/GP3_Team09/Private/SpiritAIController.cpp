#include "SpiritAIController.h"

#include "GlyphProvider.h"
#include "Interaction.h"
#include "SpiritDialogueWidget.h"
#include "SpiritPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

ASpiritAIController::ASpiritAIController()
{
	SpiritStateManager = CreateDefaultSubobject<USpiritAIStateManager>(TEXT("AIStateManager"));
}

void ASpiritAIController::BeginPlay()
{
	Super::BeginPlay();
	
	SetPlayerTarget();
	if (!SpiritStateManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("StateManager not Initialized!"));
	}
}

void ASpiritAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ASpiritPawn* const Spirit = Cast<ASpiritPawn>(InPawn))
	{
		if (UBehaviorTree* const Tree = Spirit->GetBehaviorTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(Tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(Tree);
		}
	}
}

void ASpiritAIController::SetPlayerTarget()
{
	if (Blackboard)
	{
		// get player
		if (auto* const Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			Blackboard->SetValueAsObject(PlayerTargetKeyName, Player);
		}
	}
}

void ASpiritAIController::SetAIState(ESpiritState NewState)
{
	if (SpiritStateManager)
	{
		SpiritStateManager->ChangeState(NewState);
	}
}

void ASpiritAIController::SetAILevelStage(ESpiritLevelStage NewStage)
{
	if (SpiritStateManager)
	{
		SpiritStateManager->SetLevelStage(NewStage);
	}
}

void ASpiritAIController::SetWaypointIndex(int NewIndex)
{
	if (SpiritStateManager)
	{
		SpiritStateManager->SetWaypointIndex(NewIndex);
	}
}

int ASpiritAIController::GetWaypointIndex() const
{
	if (Blackboard)
	{
		return Blackboard->GetValueAsInt("WaypointIndex");
	}
	return 0;
}