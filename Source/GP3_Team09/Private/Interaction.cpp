#include "Interaction.h"
#include "InteractionWidget.h"
#include "PlayerCharacter.h"
#include "PlayerCharacterInteract.h"
#include "SpiritAIController.h"
#include "SpiritPawn.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

void UInteraction::SetEnabled(const bool NewIsEnabled)
{
	if (IsEnabled == NewIsEnabled)
	{
		return;
	}
	IsEnabled = NewIsEnabled;
	if (PlayerCharacterInteract == nullptr)
	{
		return;
	}
	if (IsEnabled)
	{
		if (InRange)
		{
			PlayerCharacterInteract->AddInteraction(this);
		}
	} else
	{
		PlayerCharacterInteract->RemoveInteraction(this);
	}
}

bool UInteraction::DelegateIsBound(EInteractionType InteractionType) const
{
	switch (InteractionType) {
	case EInteractionType::Regular:
		return Interacted.IsBound();
	case EInteractionType::Glyph:
		return GlyphInteracted.IsBound();
	case EInteractionType::Point:
		return Pointed.IsBound();
	}
	return false;
}

TArray<EInteractionType> UInteraction::GetBoundInteractionTypes() const
{
	TArray<EInteractionType> BoundInteractionTypes;
	if (Interacted.IsBound())
	{
		BoundInteractionTypes.Add(EInteractionType::Regular);
	}
	if (GlyphInteracted.IsBound())
	{
		BoundInteractionTypes.Add(EInteractionType::Glyph);
	}
	if (Pointed.IsBound())
	{
		BoundInteractionTypes.Add(EInteractionType::Point);
	}
	return BoundInteractionTypes;
}

UInteraction::UInteraction()
{
}

void UInteraction::BeginPlay()
{
	CollisionMesh = Cast<USphereComponent>(GetOwner()->AddComponentByClass(USphereComponent::StaticClass(), false, FTransform(), false));
	GetOwner()->AddInstanceComponent(CollisionMesh);
	CollisionMesh->SetUsingAbsoluteScale(true);
	CollisionMesh->SetSphereRadius(InteractionRadius);
	
	if (ensureMsgf(SpawnWidget, TEXT("%s is missing a SpawnWidget"), *GetName()))
	{
		InstanceSpawnWidget = Cast<UWidgetComponent>(GetOwner()->AddComponentByClass(UWidgetComponent::StaticClass(), false, FTransform(), false));
		GetOwner()->AddInstanceComponent(InstanceSpawnWidget);
		InstanceSpawnWidget->SetWidgetClass(SpawnWidget);
		InstanceSpawnWidget->SetRelativeLocation(FVector(0, 0, ZOffset), false);
		InstanceSpawnWidget->SetVisibility(false);
		InstanceSpawnWidget->SetWidgetSpace(EWidgetSpace::Screen);
		// PAIN AND SUFFERING
		InstanceSpawnWidget->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
		if (InstanceSpawnWidget->GetWidget()->IsA<UInteractionWidget>() && !CanPointToSpirit)
		{
			UInteractionWidget* Widget = Cast<UInteractionWidget>(InstanceSpawnWidget->GetWidget());
			Widget->ChangeInteractionIcon(IsPuzzle);
			if (!IsInteractable)
			{
				Widget->DisableInteractionImage();
			}
			if (!CanPointToSpirit)
			{
				Widget->DisableSpiritImage();
			}
		}
	}
	TArray<AActor*> Spirits;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpiritAIController::StaticClass(), Spirits);
	if (Spirits.Num() > 0)
	{
		SpiritController = Cast<ASpiritAIController>(Spirits[0]);
		if (auto* const Pawn  = Cast<ASpiritPawn>(SpiritController->GetPawn()))
		{
			Spirit = Pawn;
		}
	}
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &UInteraction::HandleBeginOverlap);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &UInteraction::HandleEndOverlap);
	// This calls the Blueprint Event "Begin Play", of Blueprint classes that inherit from this class, and should therefore happens after the C++ code.
	Super::BeginPlay();
}

// Rider is wrong, the AActor* can't be const because the OnComponentBeginOverlap.AddDynamic wouldn't work.
// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UInteraction::HandleBeginOverlap(UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent*, int32, bool, const FHitResult&)
{
	if (OtherActor->IsA<APlayerCharacter>() && !InRange)
	{
		InRange = true;
		PlayerCharacterInteract = OtherActor->FindComponentByClass<UPlayerCharacterInteract>();
		if (IsEnabled)
		{
			PlayerCharacterInteract->AddInteraction(this);
		}
	}
}

// Rider is wrong, the AActor* can't be const because the OnComponentEndOverlap.AddDynamic wouldn't work.
// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UInteraction::HandleEndOverlap(UPrimitiveComponent*, AActor* OtherActor, UPrimitiveComponent*, int32)
{
	// Never call RemoveInteraction on priority Interactions because they are carried, so their collision is
	// disabled to not mess with player movement, so HandleEndOverlap is called even when the player
	// is still spatially overlapping the sphere.
	if (OtherActor->IsA<APlayerCharacter>() && InRange && !bIsPriority)
	{
		InRange = false;
		PlayerCharacterInteract->RemoveInteraction(this);
	}
}

void UInteraction::Interact()
{
	Interacted.Broadcast();
}
void UInteraction::GlyphInteract()
{
	GlyphInteracted.Broadcast();
}
void UInteraction::Point()
{
	Pointed.Broadcast(this);
	if (CanPointToSpirit)
	{
		Spirit->ChangeGlyph(HeldSentence);
		SpiritController->SetAIState(ESpiritState::Talk);
	}
}

