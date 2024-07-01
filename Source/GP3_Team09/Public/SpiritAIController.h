#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SpiritAIStateManager.h"
#include "SpiritAIController.generated.h"

class UInteraction;
class USpiritDialogueWidget;

UCLASS()
class GP3_TEAM09_API ASpiritAIController : public AAIController
{
    GENERATED_BODY()

public:
    explicit ASpiritAIController();

    void SetPlayerTarget();

    UFUNCTION(BlueprintCallable)
    void SetAIState(ESpiritState NewState);

    UFUNCTION(BlueprintCallable)
    void SetAILevelStage(ESpiritLevelStage NewStage);

    UFUNCTION(BlueprintCallable, Category = "Waypoint")
    void SetWaypointIndex(int NewIndex);

    UFUNCTION(BlueprintCallable, Category = "Waypoint")
    int GetWaypointIndex() const;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    USpiritAIStateManager* SpiritStateManager;

protected:
    virtual void BeginPlay() override;

    virtual void OnPossess(APawn* InPawn) override;
    
private:
    FName const PlayerTargetKeyName = "PlayerTarget";
};