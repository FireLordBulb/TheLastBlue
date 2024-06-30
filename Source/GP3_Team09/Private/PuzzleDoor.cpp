#include "PuzzleDoor.h"
#include "Engine/StaticMesh.h"

// Sets default values
APuzzleDoor::APuzzleDoor()
{
	Body = CreateDefaultSubobject<USceneComponent>("Body");
	RootComponent = Body;
}

// Called when the game starts or when spawned
void APuzzleDoor::BeginPlay()
{
	Super::BeginPlay();
}