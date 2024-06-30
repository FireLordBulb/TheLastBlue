// Fill out your copyright notice in the Description page of Project Settings.


#include "GlyphProvider.h"
#include "GlyphLibrary.h"
#include "PlainSentence.h"
#include "GlyphTextureGenerator/GlyphTextureGenerator.h"


int UGlyphProvider::GlyphPositionToInt(EGlyphPosition glyphPosition)const 
{
	return glyphPosition;
}

EGlyphPosition UGlyphProvider::IntToGlyphPosition(int integer) const
{
	return  static_cast<EGlyphPosition>(integer);
}

TArray<FVector2f> UGlyphProvider::GetOffsetData() const
{
	return GetOffsetData(SentenceData);
}

TArray<FVector2f> UGlyphProvider::GetOffsetData(const FSentence& Sentence) const
{
	TArray<FVector2f> result = TArray<FVector2f>();
	for (auto prop : Sentence.Propositions)
	{
		result.Add({0.5f,0.5f});//major glyph offset
		if(!offsetMap.Contains(prop.MajorGlyph.Texture))//Try to load in a way that doesn't trigger this
		{
			UE_LOG(LogTemp,Error,TEXT("Could not find offset of major glyph %s"), *prop.MajorGlyph.Meaning);
			result.Append(FOffsetCollection().offsets);
			continue;
		}
		result.Append(offsetMap.FindChecked((prop.MajorGlyph.Texture)).offsets);
	}
	return result;
}

// Sets default values for this component's properties
UGlyphProvider::UGlyphProvider()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	//Populate sentence data
	OnGlyphConfirmResponses = TMap<FPlainSentence,TArray<FOnGlyphConfirm>>();
}

void UGlyphProvider::ConfirmGlyph()
{
	if(!OnGlyphConfirmResponses.Contains(PlainSentenceData))return;
	for (auto callback : OnGlyphConfirmResponses[PlainSentenceData])
	{
		callback.Execute();
	}
}


void UGlyphProvider::RegisterGlyphResponse(FPlainSentence ExpectedSentence,const FOnGlyphConfirm& Response)
{
	OnGlyphConfirmResponses.FindOrAdd(ExpectedSentence).Add(Response);
}


void UGlyphProvider::CreateInitialGlyph()
{
	if(SentenceData.Propositions.IsEmpty())
	{
		UE_LOG(LogTemp,Warning,TEXT("Attempted to create glyph from empty sentence data!"));
		return;
	}
	
	if(GlyphTexture == nullptr || GlyphTexture.IsNull() || !GlyphTexture.IsValid() || /*!GlyphTexture->IsAsyncCacheComplete() ||*/ GlyphTexture.IsPending())
	{
		UE_LOG(LogTemp,Warning,TEXT("Attempted to create glyph to null texture!"));
		return;
	}
	
	
	TArray<UTexture2D*> Textures = SentenceData.GetOrderedTextureArray();
	TArray<FVector2f> offsets = GetOffsetData(SentenceData);
	UGlyphTextureGeneratorLibrary::CreateSentenceTexture(GlyphTexture.LoadSynchronous(),Textures,offsets,Masks);
	bIsDirty =false;
	
}

void UGlyphProvider::OverrideRenderTarget(UTextureRenderTarget2D* target)
{
	if(target->SizeX != 288 || target->SizeY != 288 || target->GetFormat() != RTF_RGBA8)
	{
		UE_LOG(LogTemp,Warning,TEXT("invalid render target format, must be 288x288 and r8g8b8a8"));
		return;
	}
	GlyphTexture = target;
	CreateInitialGlyph();
	
}

UTextureRenderTarget2D* UGlyphProvider::GetTextureRef()
{
	if(GlyphTexture == nullptr)
	{
		GlyphTexture = NewObject<UTextureRenderTarget2D>(GetOwner(), "DefaultGlyphRT");
		GlyphTexture-> RenderTargetFormat = RTF_RGBA8;
		GlyphTexture->ClearColor = FLinearColor::Transparent;
		GlyphTexture->bAutoGenerateMips = false;
		GlyphTexture->bCanCreateUAV = true;
		GlyphTexture->Filter = TF_Trilinear;
		GlyphTexture->InitCustomFormat(288,288,PF_B8G8R8A8,false);
		
		GlyphTexture->UpdateResourceImmediate(true);
		MakeSentenceData(PlainSentenceData,&SentenceData);
	}
	return GlyphTexture.Get();
}


FPlainSentence UGlyphProvider::GetGlyphDataSentence() const
{
	return PlainSentenceData;
}

bool UGlyphProvider::SetMinorGlyph(int propositionIndex, EGlyphPosition position, FString word)
{
	if(SentenceData.Propositions.Num() <= propositionIndex)
	{
		UE_LOG(LogTemp,Warning,TEXT("out of index range proposition"));
		return false;
	}
	bool result = true;
	result = SentenceData.Propositions[propositionIndex].SetGlyph(position, GetGlyphData(word, position));
	result = PlainSentenceData.Propositions[propositionIndex].SetWord(position,word) ? result : false;
	CreateInitialGlyph();
	return result;
}

bool UGlyphProvider::SetProposition(const int propositionIndex, const FPlainProposition& proposition)
{
	if(SentenceData.Propositions.Num() <= propositionIndex)
	{
		UE_LOG(LogTemp,Warning,TEXT("can't add proposition out of index range, try AddProposition instead."))
		return false;
	}
	FProposition propositionData;
	if(MakePropositionData(proposition,propositionData)){
		SentenceData.Propositions[propositionIndex] = propositionData;
		bIsDirty = true;
		return true;
	}
	return false;
}

bool UGlyphProvider::AddProposition(const FPlainProposition Proposition)
{
	FProposition PropositionData;
	if(!MakePropositionData(Proposition,PropositionData))return false;
	bIsDirty = true;
	SentenceData.Propositions.Add(PropositionData);
	return true;
}

bool UGlyphProvider::SetSentence(const FPlainSentence& sentence)
{
	bIsDirty = true;
	bool result = MakeSentenceData(sentence,&SentenceData);
	PlainSentenceData = sentence;
	if(result && GlyphTexture != nullptr)CreateInitialGlyph();
	return  result;
}


// Called when the game starts
void UGlyphProvider::BeginPlay()
{
	Super::BeginPlay();
	if(GlyphTexture == nullptr)return;
	GlyphTexture->UpdateResourceImmediate(false);
	CreateInitialGlyph();
}

// void UGlyphProvider::PostApplyToComponent()
// {
// 	Super::PostApplyToComponent();
// 	MakeSentenceData(PlainSentenceData,&SentenceData);
// 	if(GlyphTexture != nullptr)CreateInitialGlyph();
// }
#if WITH_EDITOR
void UGlyphProvider::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	SetSentence(PlainSentenceData);
}
#endif
UGlyphLibrary* UGlyphProvider::GetGlyphLibrary(EGlyphPosition glyphType) const
{
	UGlyphLibrary* lib;
	switch (glyphType) {
	case Major:
		lib = MajorGlyphLibrary;
		break;
	case Subject:
	case Object:
		lib = NounsGlyphLib;
		break;
	case SubAdjective:
	case ObjAdjective:
		lib = AdjectiveGlyphLib;
		break;
	case Verb:
		lib = VerbsGlyphLib;
		break;
	case Adverb:
		lib = AdverbsGlyphLib;
		break;
	case Past:
	case Future:
		lib = TenseGlyphLib;
		break;
	case Central:
		lib = CentralGlyphLib;
		break;
	case Conjunction:
		lib = ConjunctionGlyphLib;
		break;
	default:
		UE_LOG(LogTemp,Error, TEXT("Could not determine glyph library associated with the glyph type %s"),*UEnum::GetValueAsString(glyphType));
		lib = nullptr;
	}
	return lib;
}

FGlyphData UGlyphProvider::GetGlyphData(const FString& Word, EGlyphPosition glyphType) const
{
	UGlyphLibrary* lib = GetGlyphLibrary(glyphType);
	if(!lib->Dictionary.Contains(Word))
	{
		auto glyphTypeName = UEnum::GetValueAsString(glyphType);
		UE_LOG(LogTemp,Error,TEXT("Could not find word \"%s\" in %s dictionary") ,*Word,*glyphTypeName);
		return FGlyphData {Word,nullptr};
	}
	return FGlyphData{Word, lib->Dictionary[Word]};
}

bool UGlyphProvider::TryMakeGlyphData(const FString& Word, const TSoftObjectPtr<UGlyphLibrary>& Library,
	FGlyphData* GlyphData)
{
	GlyphData->Meaning = Word;
	if(Word.IsEmpty())
	{
		GlyphData->Texture = nullptr;//might need a fallback texture here
		return true;
	}
	
	if(Library.IsNull() || !Library->Dictionary.Contains(Word))
	{
		UE_LOG(LogTemp,Error,TEXT("Could not find word \" %s \" in  %s") ,*Word,*Library.ToString());
		GlyphData->Texture = nullptr;
		return false;
	}
	
	GlyphData->Texture = Library->Dictionary[Word];
	return true;
}

bool UGlyphProvider::MakePropositionData(const FPlainProposition& Proposition, FProposition& PropositionData)
{
	bool result = true;
	result = TryMakeGlyphData(Proposition.Case,MajorGlyphLibrary,&PropositionData.MajorGlyph) ? result : false;
	result = TryMakeGlyphData(Proposition.Subject,NounsGlyphLib,&PropositionData.SubjectGlyph) ? result : false;
	result = TryMakeGlyphData(Proposition.SubjectAdjective,AdjectiveGlyphLib, &PropositionData.SubjectAdjectiveGlyph) ? result : false;
	result = TryMakeGlyphData(Proposition.Verb,VerbsGlyphLib,&PropositionData.VerbGlyph) ? result : false;
	result = TryMakeGlyphData(Proposition.Adverb,AdverbsGlyphLib,&PropositionData.AdverbGlyph) ? result : false;
	result = TryMakeGlyphData(Proposition.Object,NounsGlyphLib,&PropositionData.ObjectGlyph) ? result : false;
	result = TryMakeGlyphData(Proposition.ObjectAdjective,AdjectiveGlyphLib,&PropositionData.ObjectAdjectiveGlyph) ? result : false;
	result = TryMakeGlyphData(Proposition.Past,TenseGlyphLib,&PropositionData.PastGlyph) ? result : false;
	result = TryMakeGlyphData(Proposition.Future,TenseGlyphLib,&PropositionData.FutureGlyph) ? result : false;
	result = TryMakeGlyphData(Proposition.Central,CentralGlyphLib,&PropositionData.CentralGlyph) ? result : false;
	result = TryMakeGlyphData(Proposition.Conjunction,ConjunctionGlyphLib,&PropositionData.ConjunctionVerbData) ? result : false;
	return result;
}

bool UGlyphProvider::MakeSentenceData(const FPlainSentence& Sentence, FSentence* SentenceRef)
{
	FSentence NewSentence = FSentence();
	bool result = true;
	for (auto plainProp : Sentence.Propositions)
	{
		FProposition parsedProp;
		result = MakePropositionData(plainProp,parsedProp) ? result : false;
		NewSentence.Propositions.Add(parsedProp);
	}
	*SentenceRef = NewSentence;
	return result;
}


// Called every frame
void UGlyphProvider::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(bIsDirty)
	{
		CreateInitialGlyph();
	}
}
