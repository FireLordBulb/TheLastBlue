#pragma once
#include "IPropertyTypeCustomization.h"
#include "EditorUndoClient.h"


struct FPlainSentence;
class UGlyphLibrary;

class FPlainSentenceCustomization : public IPropertyTypeCustomization, FEditorUndoClient
{
public:
	FPlainSentenceCustomization(
		const UGlyphLibrary &NounLibrary,
		const UGlyphLibrary &VerbLibrary,
		const UGlyphLibrary &AdjectiveLibrary,
		const UGlyphLibrary &TenseLibrary,
		const UGlyphLibrary &CentralLibrary,
		const UGlyphLibrary &ConjunctionLibrary);
	FPlainSentenceCustomization();
	
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;
	
	void OnPropertyValueChanged();
	void OnSearchForGlyph() const;
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

private:
	TSharedPtr<FPlainSentence> InspectedSentence;//the plain sentence we want tot edit

	/** Cached property handle */
	TSharedPtr<IPropertyHandle> StructPropertyHandle;
	
};
