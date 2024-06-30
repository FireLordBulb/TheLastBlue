// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlainSentence.h"
#include "Sentence.h"
#include "Components/ActorComponent.h"
#include "GlyphProvider.generated.h"


class UGlyphLibrary;
struct FPlainProposition;
enum EGlyphPosition : int8;

USTRUCT()
struct FOffsetCollection
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TArray<FVector2f> offsets = {{0.0f,0.0f},
									{0.0f,0.0f},
									{0.0f,0.0f},
									{0.0f,0.0f},
									{0.0f,0.0f},
									{0.0f,0.0f},
									{0.0f,0.0f},
									{0.0f,0.0f},
									{0.0f,0.0f},
									{0.0f,0.0f}
								};
};

DECLARE_DYNAMIC_DELEGATE(FOnGlyphConfirm);

UCLASS(ClassGroup=(Glyphs),Blueprintable,Abstract,HideCategories("Replication","Collision","AssetUserData","ComponentReplication","ComponentTick","Activation"))
class SENTENCEBUILDER_API UGlyphProvider : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	int GlyphPositionToInt(EGlyphPosition glyphPosition) const;
	UFUNCTION(BlueprintCallable)
	EGlyphPosition IntToGlyphPosition(int integer) const;
	UFUNCTION(BlueprintCallable)
	TArray<FVector2f> GetOffsetData() const;
	
	TArray<FVector2f> GetOffsetData(const FSentence& Sentence) const;
	// Sets default values for this component's properties
	UGlyphProvider();

	UFUNCTION(BlueprintCallable)
	void ConfirmGlyph();//TODO where should this happen ?

	
	UFUNCTION(BlueprintCallable,meta = (AutoCreateRefTerm = "Delegate"))
	void RegisterGlyphResponse(FPlainSentence ExpectedSentence, const FOnGlyphConfirm& Response);
	
	
	UFUNCTION(BlueprintCallable)
	void OverrideRenderTarget(UTextureRenderTarget2D* target);
	UFUNCTION(BlueprintCallable)
	UTextureRenderTarget2D* GetTextureRef();
	UFUNCTION(BlueprintCallable)
	FPlainSentence GetGlyphDataSentence() const;
	
	UFUNCTION(BlueprintCallable)
	bool SetMinorGlyph(int propositionIndex, EGlyphPosition position, FString word);//todo: drop down for this
	UFUNCTION(BlueprintCallable)
	bool SetProposition(const int propositionIndex,const FPlainProposition& proposition);
	UFUNCTION(BlueprintCallable)
	bool AddProposition(const FPlainProposition Proposition);
	UFUNCTION(BlueprintCallable)
	bool SetSentence(const FPlainSentence& sentence);
	std::initializer_list<UE::Math::TIntVector2<unsigned int>> GetMaskData(const FSentence& Sentence);
	UFUNCTION(BlueprintCallable)
	void CreateInitialGlyph();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//virtual void PostApplyToComponent() override;
#if WITH_EDITOR
	virtual  void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	UGlyphLibrary* GetGlyphLibrary(EGlyphPosition glyphType) const;
	FGlyphData GetGlyphData(const FString& Word, EGlyphPosition glyphType) const;
	static bool TryMakeGlyphData(const FString &Word, const TSoftObjectPtr<UGlyphLibrary>& Library, FGlyphData* GlyphData);
	bool MakePropositionData(const FPlainProposition& Proposition, FProposition& PropositionData);
	bool MakeSentenceData(const FPlainSentence& Sentence, FSentence* SentenceREf);
	
	UPROPERTY(VisibleInstanceOnly)
	TSoftObjectPtr<UTextureRenderTarget2D> GlyphTexture;
	UPROPERTY(VisibleInstanceOnly)
	FSentence SentenceData;
	TMap<FPlainSentence,TArray<FOnGlyphConfirm>> OnGlyphConfirmResponses;
private:
	UPROPERTY(EditDefaultsOnly,AdvancedDisplay,Category="Libraries")
	bool bOverrideLibraries = false;
	UPROPERTY(EditAnywhere)//Will be edited to be not be not directly editable to not circumvent the texture refresh
	FPlainSentence PlainSentenceData;
	UPROPERTY(EditDefaultsOnly, Category="Libraries",meta=(EditCondition="bOverrideLibraries==true"))
	UGlyphLibrary* MajorGlyphLibrary;
	UPROPERTY(EditDefaultsOnly,Category=Libraries,meta=(EditCondition="bOverrideLibraries==true"))
	UGlyphLibrary* NounsGlyphLib;
	UPROPERTY(EditDefaultsOnly,Category=Libraries,meta=(EditCondition="bOverrideLibraries==true"))
	UGlyphLibrary* VerbsGlyphLib;
	UPROPERTY(EditDefaultsOnly,Category=Libraries,meta=(EditCondition="bOverrideLibraries==true"))
	UGlyphLibrary* AdjectiveGlyphLib;
	UPROPERTY(EditDefaultsOnly,Category=Libraries,meta=(EditCondition="bOverrideLibraries==true"))
	UGlyphLibrary* AdverbsGlyphLib;
	UPROPERTY(EditDefaultsOnly,Category=Libraries,meta=(EditCondition="bOverrideLibraries==true"))
	UGlyphLibrary* TenseGlyphLib;
	UPROPERTY(EditDefaultsOnly,Category=Libraries,meta=(EditCondition="bOverrideLibraries==true"))
	UGlyphLibrary* CentralGlyphLib;
	UPROPERTY(EditDefaultsOnly,Category=Libraries,meta=(EditCondition="bOverrideLibraries==true"))
	UGlyphLibrary* ConjunctionGlyphLib;

	UPROPERTY(EditDefaultsOnly,Category=Offsets,meta=(EditCondition="bOverrideLibraries==true"))
	TMap<UTexture2D*,FOffsetCollection> offsetMap;
	bool bIsDirty= false;
	
	const TArray<FUintVector2> Masks = {//Not ideal to store it here
		FUintVector2(0u,1u),//Major
		FUintVector2(0u,2u),//Subject
		FUintVector2(0u,4u),//Subject adjective
		FUintVector2(0u,8u),// Verb
		FUintVector2(0u,16u),//Adverb
		FUintVector2(0u,32u),//Object
		FUintVector2(0u,64u),//ObjectAdjective
		FUintVector2(0u,128u),//Past
		FUintVector2(1u,0u),//Future
		FUintVector2(2u,0u),//Central
		FUintVector2(4u,0u),//Conjunction
	};
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
};


