// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestPreviewViewportCommands.h"

#define LOCTEXT_NAMESPACE "FTestPreviewViewportModule"

void FTestPreviewViewportCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "TestPreviewViewport", "Bring up TestPreviewViewport window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
