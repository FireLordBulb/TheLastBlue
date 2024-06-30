#include "PlainSentenceCustomization.h"

#include "DetailWidgetRow.h"
//#include "Editor.h"
#include "IDetailChildrenBuilder.h"
#include "PlainSentence.h"
#include "PropertyHandle.h"


FPlainSentenceCustomization::FPlainSentenceCustomization()
{
}

void FPlainSentenceCustomization::PostUndo(bool bSuccess)
{
	FEditorUndoClient::PostUndo(bSuccess);
}

void FPlainSentenceCustomization::PostRedo(bool bSuccess)
{
	FEditorUndoClient::PostRedo(bSuccess);
}

void FPlainSentenceCustomization::OnPropertyValueChanged()
{
}

void FPlainSentenceCustomization::OnSearchForGlyph() const
{
}

void FPlainSentenceCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle,
                                                  FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	InspectedSentence = MakeShareable(new FPlainSentence);//I may need to deserialize here, or it might be used as a working copy
	StructPropertyHandle = PropertyHandle;//caching property handle

	FSimpleDelegate OnGlyphChanged = FSimpleDelegate::CreateSP(this, &FPlainSentenceCustomization::OnPropertyValueChanged);
	StructPropertyHandle->SetOnPropertyValueChanged((OnGlyphChanged));//I could als register to children here instead to reduce overhead of recomputing

	//building something here

	FUIAction SearchForGlyphRefAction(FExecuteAction::CreateSP(this, &FPlainSentenceCustomization::OnSearchForGlyph));

	HeaderRow
	.NameContent()
	[
		StructPropertyHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MaxDesiredWidth(512);
	//GEditor->RegisterForUndo(this);//handled by the parent here
}

void FPlainSentenceCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle,
	IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	ChildBuilder.AddProperty((PropertyHandle->GetChildHandle("Propositions").ToSharedRef()));
}

TSharedRef<IPropertyTypeCustomization> FPlainSentenceCustomization::MakeInstance()
{
	return MakeShareable(new FPlainSentenceCustomization());
}
