#include "SentenceBuilderEditor.h"
#include "PropertyEditorModule.h"
#include "PlainSentenceCustomization.h"

#define LOCTEXT_NAMESPACE "FSentenceBuilderEditorModule"

void FSentenceBuilderEditorModule::StartupModule()
{
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.RegisterCustomPropertyTypeLayout(
        "PlainSentence",
        FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FPlainSentenceCustomization::MakeInstance));
}

void FSentenceBuilderEditorModule::ShutdownModule()
{
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.UnregisterCustomPropertyTypeLayout("PlainSentence");
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSentenceBuilderEditorModule, SentenceBuilderEditor)