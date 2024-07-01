// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Speak.generated.h"

class USpiritDialogueWidget;

UCLASS()
class UBTTask_Speak : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	public:
		explicit UBTTask_Speak();
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
