#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckPlayerDistance.generated.h"

UCLASS()
class UBTService_CheckPlayerDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	

public: 
	explicit UBTService_CheckPlayerDistance();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, Category = "AI" , meta = (AllowPrivateAccess = "true"))
	float MaxDistanceThreshold = 2000.f;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float MinDistanceThreshold = 1000.f;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float TalkDistanceThreshold = 200.f;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float MaxWalkThreshold = 800.f;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (AllowPrivateAccess = "true"))
	float MinWalkThreshold = 400.f;
};
