#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaypointPath.generated.h"

UCLASS()
class AWaypointPath : public AActor
{
	GENERATED_BODY()
	
public:	
	AWaypointPath();

	FVector GetWaypoint(int const index) const;
	int Num() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TArray<FVector> Waypoints;
};
