// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BTTask_StopSpeaking.h"
#include "SpiritAIController.h"
#include "SpiritPawn.h"


UBTask_StopSpeaking::UBTask_StopSpeaking()
{
	NodeName = "Stop talking";
}


EBTNodeResult::Type UBTask_StopSpeaking::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
