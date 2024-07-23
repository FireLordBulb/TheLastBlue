#pragma once

#include "CoreMinimal.h"
#include "GlyphProvider.h"
#include "Interaction.h"
#include "PlainSentence.h"
#include "WaypointPath.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "SpiritAIStates.h"
#include "SpiritPawn.generated.h"

class UPlayerWordCollection;
class USpiritDialogueWidget;

UCLASS()
class GP3_TEAM09_API ASpiritPawn : public ACharacter
{
	GENERATED_BODY()

public:
	ASpiritPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTree() const;
	
	AWaypointPath* GetWaypointPath() const;

	void OnSetAIState();

	void OnSetAIStage();

	UFUNCTION()
	void ShowGlyph();

	UFUNCTION()
	void DisableGlyph();

	UFUNCTION(BlueprintCallable)
	void ChangeGlyph(FPlainSentence Sentence);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UPlayerWordCollection> playerJournalData;

private:
	UPROPERTY()
	FPlainSentence SpiritSpeakSentence;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	USpiritDialogueWidget* DialogueElement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess="true"))
	UBehaviorTree* Tree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess="true"))
	AWaypointPath* WaypointPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool ChangeState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool ChangeStage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	ESpiritState State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	ESpiritLevelStage Stage;
};