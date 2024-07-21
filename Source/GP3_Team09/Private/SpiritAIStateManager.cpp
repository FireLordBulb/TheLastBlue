#include "SpiritAIStateManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpiritAIController.h"
#include "SpiritPawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


void USpiritAIStateManager::ChangeState(ESpiritState NewState)
{
	if (NewState != CurrentState)
	{
		ASpiritPawn* Spirit = Cast<ASpiritPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpiritPawn::StaticClass()));
		if (Spirit)
		{
			ASpiritAIController* Controller = Cast<ASpiritAIController>(Spirit->GetController());
			if(Controller)
			{
				UBlackboardComponent* Blackboard = Controller->GetBlackboardComponent();
				if(Blackboard)
				{
					PreviousState = CurrentState;
					CurrentState = NewState;
					Blackboard->SetValueAsEnum("State", static_cast<uint8>(NewState));
				}
			}
		}
	}
}

void USpiritAIStateManager::SetLevelStage(ESpiritLevelStage NewStage)
{
	CurrentStage = NewStage;
	ASpiritPawn* Spirit = Cast<ASpiritPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpiritPawn::StaticClass()));
	if (Spirit)
	{
		ASpiritAIController* Controller = Cast<ASpiritAIController>(Spirit->GetController());
		if (Controller)
		{
			UBlackboardComponent* Blackboard = Controller->GetBlackboardComponent();
			if (Blackboard)
			{
				switch (CurrentStage)
				{
				case ESpiritLevelStage::StageOne:
					SetMovementSpeed(ESpiritMovementSpeed::Normal);
					Blackboard->SetValueAsEnum("Stage", static_cast<uint8>(ESpiritLevelStage::StageOne));
					break;
				case ESpiritLevelStage::StageTwo:
					SetMovementSpeed(ESpiritMovementSpeed::Slow);
					Blackboard->SetValueAsEnum("Stage", static_cast<uint8>(ESpiritLevelStage::StageTwo));
					break;
				case ESpiritLevelStage::StageThree:
					SetMovementSpeed(ESpiritMovementSpeed::Normal);
					Blackboard->SetValueAsEnum("Stage", static_cast<uint8>(ESpiritLevelStage::StageThree));
					break;
				}
				Blackboard->SetValueAsBool("ChangeStage", true);
			}
		}
	}
}

void USpiritAIStateManager::SetMovementSpeed(ESpiritMovementSpeed NewSpeed)
{
	CurrentMovementSpeed = NewSpeed;
	ASpiritPawn* Spirit = Cast<ASpiritPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpiritPawn::StaticClass()));
	if (Spirit)
	{
		ASpiritAIController* Controller = Cast<ASpiritAIController>(Spirit->GetController());
		if (Controller)
		{
			auto CharacterMovement = Spirit->GetCharacterMovement();

			switch (CurrentMovementSpeed)
			{
			case ESpiritMovementSpeed::Slow:
				CharacterMovement->MaxWalkSpeed = 250.f;
				break;
			case ESpiritMovementSpeed::Normal:
				CharacterMovement->MaxWalkSpeed = 300.f;
				break;
			case ESpiritMovementSpeed::Fast:
				CharacterMovement->MaxWalkSpeed = 500.f;
				break;
			}
		}
	}
}

void USpiritAIStateManager::SetWaypointIndex(int NewIndex)
{
	ASpiritPawn* Spirit = Cast<ASpiritPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpiritPawn::StaticClass()));
	if (Spirit)
	{
		ASpiritAIController* Controller = Cast<ASpiritAIController>(Spirit->GetController());
		if(Controller)
		{
			UBlackboardComponent* Blackboard = Controller->GetBlackboardComponent();
			if(Blackboard)
			{
				Blackboard->SetValueAsInt("WaypointIndex", NewIndex);
			}
		}
	}
}

ESpiritState USpiritAIStateManager::GetCurrentState() const
{
	ASpiritPawn* Spirit = Cast<ASpiritPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpiritPawn::StaticClass()));
	if (Spirit)
	{
		ASpiritAIController* Controller = Cast<ASpiritAIController>(Spirit->GetController());
		if(Controller)
		{
			UBlackboardComponent* Blackboard = Controller->GetBlackboardComponent();
			if(Blackboard)
			{
				return static_cast<ESpiritState>(Blackboard->GetValueAsEnum("State"));
			}
		}
	}
	return CurrentState;
}

ESpiritState USpiritAIStateManager::GetPreviousState() const
{
	return PreviousState;
}

ESpiritLevelStage USpiritAIStateManager::GetCurrentStage() const
{
	return CurrentStage;
}

ESpiritMovementSpeed USpiritAIStateManager::GetCurrentSpeed() const
{
	return CurrentMovementSpeed;
}

void USpiritAIStateManager::ChangeGlyph(FPlainSentence Sentence)
{
	ASpiritPawn* Spirit = Cast<ASpiritPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpiritPawn::StaticClass()));
	if (Spirit)
	{
		Spirit->ChangeGlyph(Sentence);
	}
}
