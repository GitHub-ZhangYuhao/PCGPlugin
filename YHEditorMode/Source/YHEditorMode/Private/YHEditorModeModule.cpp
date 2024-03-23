// Copyright Epic Games, Inc. All Rights Reserved.

#include "YHEditorModeModule.h"
#include "YHEditorModeEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "YHEditorModeModule"

void FYHEditorModeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FYHEditorModeEditorModeCommands::Register();
}

void FYHEditorModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FYHEditorModeEditorModeCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FYHEditorModeModule, YHEditorModeEditorMode)