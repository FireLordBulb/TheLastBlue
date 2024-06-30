#include "PlayerCharacterInteract.h"
#include "Interaction.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"

UPlayerCharacterInteract::UPlayerCharacterInteract()
{
	PrimaryComponentTick.bCanEverTick = true;
} 

void UPlayerCharacterInteract::BeginPlay()
{
	Super::BeginPlay();
	Owner = this->GetOwner();
	Camera = Owner->FindComponentByClass<UCameraComponent>();
}

void UPlayerCharacterInteract::AddInteraction(UInteraction* NewInteraction)
{
	ensure(NewInteraction);
	CloseInteractions.Add(NewInteraction);
	PrimaryComponentTick.bCanEverTick = true;
	for (auto& InteractionType : NewInteraction->GetBoundInteractionTypes()) 
	{
		if (!ClosestInteractions.Contains(InteractionType) || ClosestInteractions[InteractionType] == nullptr)
		{
			SetClosestInteraction(NewInteraction, InteractionType);
		}
	}
}

void UPlayerCharacterInteract::RemoveInteraction(UInteraction* InteractionToRemove)
{
	if (!CloseInteractions.Contains(InteractionToRemove))
	{
		return;
	}
	CloseInteractions.Remove(InteractionToRemove);
	// An exception happens if the TMap is iterated directly. Converting it to a TArray first works.
	for (auto& Tuple : ClosestInteractions.Array()) 
	{
		if (InteractionToRemove == Tuple.Value)
		{
			SetClosestInteraction(nullptr, Tuple.Key);
		}
	}
}

UInteraction* UPlayerCharacterInteract::GetClosestInteraction(const EInteractionType InteractionType)
{
	if (!ClosestInteractions.Contains(InteractionType))
	{
		return nullptr;
	}
	return ClosestInteractions[InteractionType];
}

void UPlayerCharacterInteract::SetClosestInteraction(UInteraction* NewInteraction, EInteractionType InteractionType)
{
	if (ClosestInteractions.Contains(InteractionType) && ClosestInteractions[InteractionType] != nullptr)
	{
		ClosestInteractions[InteractionType]->InstanceSpawnWidget->SetVisibility(false);
	}
	ClosestInteractions.Add(InteractionType, NewInteraction);
	if (NewInteraction != nullptr)
	{
		NewInteraction->InstanceSpawnWidget->SetVisibility(true);
	}
}

void UPlayerCharacterInteract::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (CloseInteractions.Num() <= 1)
	{
		CurrentTimer = 0;
		return;
	}
	CurrentTimer += DeltaTime;
	if (CurrentTimer >= UpdateClosestPeriod)
	{
		CurrentTimer = 0;
		MultipleInteractions();
	}
}

void UPlayerCharacterInteract::MultipleInteractions()
{
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, Camera->GetComponentLocation(), Camera->GetComponentLocation() + Camera->GetForwardVector() * 1000, ECC_Visibility);
	FVector Location = Hit.bBlockingHit ? Hit.Location : Owner->GetActorLocation();
	// An exception happens if the TMap is iterated directly. Converting it to a TArray first works.
	for (auto& Tuple : ClosestInteractions.Array())
	{
		RecalculateClosestInteraction(Location, Tuple.Key);
	}
}

void UPlayerCharacterInteract::RecalculateClosestInteraction(const FVector& Location, const EInteractionType InteractionType)
{
	UInteraction* NewClosest = nullptr;
	// This value doesn't matter since NewClosest will be nullptr for the first normal valid UInteraction,
	// short-circuiting the boolean expression.
	float ClosestDistance = 0;
	for (UInteraction* Interaction : CloseInteractions)
	{
		if (!Interaction->DelegateIsBound(InteractionType))
		{
			continue;
		}
		// Always use the first priority UInteraction if there is one, regardless of distance.
		if (Interaction->bIsPriority)
		{
			NewClosest = Interaction;
			break;
		}
		float CurrentDistance = FVector::DistSquared(Interaction->GetOwner()->GetActorLocation(), Location);
		if (NewClosest == nullptr || CurrentDistance < ClosestDistance)
		{
			NewClosest = Interaction;
			ClosestDistance = CurrentDistance;
		}	
	}
	SetClosestInteraction(NewClosest, InteractionType);
}



