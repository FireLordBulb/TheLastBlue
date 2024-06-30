// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BTTask_Speak.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpiritAIController.h"
#include "SpiritPawn.h"

UBTTask_Speak::UBTTask_Speak()
{
	NodeName = "Speak with Player";
}

EBTNodeResult::Type UBTTask_Speak::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* const Controller = Cast<ASpiritAIController>(OwnerComp.GetAIOwner()))
	{
		if (auto* const Pawn  = Cast<ASpiritPawn>(Controller->GetPawn()))
		{
			Pawn->ShowGlyph();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}