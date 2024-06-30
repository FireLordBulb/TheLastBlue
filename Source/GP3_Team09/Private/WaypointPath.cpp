#include "WaypointPath.h"

AWaypointPath::AWaypointPath()
{
	PrimaryActorTick.bCanEverTick = false;
}

FVector AWaypointPath::GetWaypoint(int const index) const
{
	return Waypoints[index];
}

int AWaypointPath::Num() const
{
	return Waypoints.Num();
}

