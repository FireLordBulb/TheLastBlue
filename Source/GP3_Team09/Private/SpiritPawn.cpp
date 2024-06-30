#include "SpiritPawn.h"

#include "GlyphProvider.h"
#include "SpiritAIController.h"
#include "Interaction.h"
#include "PlayerWordCollection.h"
#include "PlayerWordCollection.h"
#include "SpiritDialogueWidget.h"

void ASpiritPawn::BeginPlay()
{
	Super::BeginPlay();
}

ASpiritPawn::ASpiritPawn()
{
	
}

void ASpiritPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ChangeState)
	{
		OnSetAIState();
		ChangeState = false;
	}

	if (ChangeStage)
	{
		OnSetAIStage();
		ChangeStage = false;
	}
}

void ASpiritPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UBehaviorTree* ASpiritPawn::GetBehaviorTree() const
{
	return Tree;
}

AWaypointPath* ASpiritPawn::GetWaypointPath() const
{
	return WaypointPath;
}

void ASpiritPawn::OnSetAIState()
{
	auto* SpiritAIController = Cast<ASpiritAIController>(GetController());
	if (SpiritAIController)
	{
		SpiritAIController->SetAIState(State);
	}
}

void ASpiritPawn::OnSetAIStage()
{
	auto* SpiritAIController = Cast<ASpiritAIController>(GetController());
	if (SpiritAIController)
	{
		SpiritAIController->SetAILevelStage(Stage);
	}
}

void ASpiritPawn::ShowGlyph()
{
	if (DialogueElement != nullptr)
	{
		if (DialogueElement->IsVisible())
			DialogueElement->DisableGlyph();
		else
			DialogueElement->EnableGlyph();
	}
}

void ASpiritPawn::ChangeGlyph(FPlainSentence Sentence)
{
	if(playerJournalData.IsValid())playerJournalData.Get()->AddMissingWordsFromSentence(Sentence);
	UGlyphProvider* GlyphProvider = GetComponentByClass<UGlyphProvider>();
	GlyphProvider->SetSentence(Sentence);
}