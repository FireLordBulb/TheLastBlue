// Copyright Epic Games, Inc. All Rights Reserved.

#include "GP3_CustomShaderLibrary.h"

#define LOCTEXT_NAMESPACE "FGP3_CustomShaderLibraryModule"

void FGP3_CustomShaderLibraryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FGP3_CustomShaderLibraryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGP3_CustomShaderLibraryModule, GP3_CustomShaderLibrary)