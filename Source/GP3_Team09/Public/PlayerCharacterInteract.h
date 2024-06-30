#pragma once

#include "PlayerCharacterInteract.generated.h"

class UCameraComponent;
class UInteraction;

enum class EInteractionType : uint8;
UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class UPlayerCharacterInteract : public UActorComponent
{
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintCallable)
		void AddInteraction(UInteraction* NewInteraction);
		UFUNCTION(BlueprintCallable)
		void RemoveInteraction(UInteraction* InteractionToRemove);

		UFUNCTION(BlueprintCallable, BlueprintPure)
		UInteraction* GetClosestInteraction(EInteractionType InteractionType);
	
		TMap<EInteractionType, UInteraction*> ClosestInteractions;
	
		UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		TArray<UInteraction*> CloseInteractions;
	
	protected:
		UPlayerCharacterInteract();
		virtual void BeginPlay() override;
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	private:
	
		void SetClosestInteraction(UInteraction* NewInteraction, EInteractionType InteractionType);

		void MultipleInteractions();

		void RecalculateClosestInteraction(const FVector& Location, EInteractionType InteractionType);
	
		float CurrentTimer = 0;

		UPROPERTY()
		AActor* Owner = nullptr;

		UPROPERTY()
		UCameraComponent* Camera = nullptr;

		/** How much time (seconds) is between the recalculations of the closest interaction of each type when there is more than 1 close interaction.*/
		UPROPERTY(EditDefaultsOnly)
		float UpdateClosestPeriod = 0.02f;
};
