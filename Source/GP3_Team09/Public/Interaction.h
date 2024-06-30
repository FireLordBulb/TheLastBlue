#pragma once
#include "CoreMinimal.h"
#include "PlainSentence.h"
#include "Blueprint/UserWidget.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Interaction.generated.h"

class UPlayerCharacterInteract;
class ASpiritAIController;
class ASpiritPawn;
class UWidgetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPoint, UInteraction*, Value);

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	Regular,
	Glyph,
	Point
};
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class UInteraction : public UActorComponent
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintCallable)
		void SetEnabled(bool IsEnabled);
	
		UPROPERTY(BlueprintReadOnly)
		bool InRange = false;

		UFUNCTION(BlueprintCallable)
		bool DelegateIsBound(EInteractionType InteractionType) const;

		UFUNCTION(BlueprintCallable)
		TArray<EInteractionType> GetBoundInteractionTypes() const;
	
		UPROPERTY(BlueprintReadOnly)
		UWidgetComponent* InstanceSpawnWidget = nullptr;

		UPROPERTY(BlueprintReadWrite)
		bool bIsPriority = false;

		UPROPERTY(EditAnywhere)
		float InteractionRadius = 300.0f;

	protected:
		UInteraction();
		virtual void BeginPlay() override;
	
		UPROPERTY(BlueprintReadOnly, EditAnywhere)
		bool CanPointToSpirit = true;

		UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		FPlainSentence HeldSentence;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* CollisionMesh = nullptr;
	
	private:
		UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
		ASpiritAIController* SpiritController = nullptr;

		UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
		ASpiritPawn* Spirit = nullptr;

		UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> SpawnWidget;

		UPROPERTY(EditDefaultsOnly)
		float ZOffset = 100.f;

		UPROPERTY(BlueprintAssignable)
		FInteract Interacted;
		UPROPERTY(BlueprintAssignable)
		FInteract GlyphInteracted;
		UPROPERTY(BlueprintAssignable)
		FPoint Pointed;

		UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = true))
		UPlayerCharacterInteract* PlayerCharacterInteract = nullptr;
	
		UFUNCTION()
		void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
		UFUNCTION()
		void HandleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

		UFUNCTION(BlueprintCallable)
		void Interact();
		UFUNCTION(BlueprintCallable)
        void GlyphInteract();
		UFUNCTION(BlueprintCallable)
		void Point();

		bool IsEnabled = true;
};