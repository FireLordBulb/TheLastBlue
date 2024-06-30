#include "NavLinkSpirit.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ANavLinkSpirit::ANavLinkSpirit()
{
	bSmartLinkIsRelevant = true;
}

void ANavLinkSpirit::HandleJump(AActor* Agent, const FVector& Destination)
{
	ACharacter* Spirit = Cast<ACharacter>(Agent);
	if (Spirit)
	{
		FVector JumpVelocity;
		FVector StartLocation = Spirit->GetActorLocation();
		FVector EndLocation = Destination;

		if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, JumpVelocity, StartLocation, EndLocation))
		{
			Spirit->LaunchCharacter(JumpVelocity, true, true);
		}
	}
}
