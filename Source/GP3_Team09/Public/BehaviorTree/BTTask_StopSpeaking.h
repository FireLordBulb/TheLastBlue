// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_StopSpeaking.generated.h"

class USpiritDialogueWidget;
/**
 * 
 */
UCLASS()
class GP3_TEAM09_API UBTask_StopSpeaking : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	public:
		explicit UBTask_StopSpeaking();
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	private:
		UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
		USpiritDialogueWidget* DialogueElement = nullptr;
};
