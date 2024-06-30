#pragma once

#include "CoreMinimal.h"
#include "SpiritAIStates.h"
#include "PlainSentence.h"
#include "SpiritAIStateManager.generated.h"


UCLASS(BlueprintType)
class USpiritAIStateManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "AI")
	void ChangeState(ESpiritState NewState);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetLevelStage(ESpiritLevelStage NewStage);

	UFUNCTION(BlueprintCallable, Category = "AI")
	void SetMovementSpeed(ESpiritMovementSpeed NewSpeed);

	UFUNCTION(BlueprintCallable, Category = "Waypoint")
	void SetWaypointIndex(int NewIndex);
	
	UFUNCTION(BlueprintCallable, Category = "AI")
	ESpiritState GetCurrentState() const;

	UFUNCTION(BlueprintCallable, Category = "AI")
	ESpiritState GetPreviousState() const;

	UFUNCTION(BlueprintCallable, Category = "AI")
	ESpiritLevelStage GetCurrentStage() const;

	UFUNCTION(BlueprintCallable, Category = "AI")
	ESpiritMovementSpeed GetCurrentSpeed() const;

	UFUNCTION(BlueprintCallable)
	void ChangeGlyph(FPlainSentence Sentence);

private:
	
	// Behaviors
	ESpiritState CurrentState;
	ESpiritState PreviousState;
	
	// Stages
	ESpiritLevelStage CurrentStage;

	// Movements
	ESpiritMovementSpeed CurrentMovementSpeed;

};
