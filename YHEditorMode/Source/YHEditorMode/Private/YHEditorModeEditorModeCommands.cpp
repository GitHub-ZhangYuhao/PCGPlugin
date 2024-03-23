// Copyright Epic Games, Inc. All Rights Reserved.

#include "YHEditorModeEditorModeCommands.h"
#include "YHEditorModeEditorMode.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "YHEditorModeEditorModeCommands"

FYHEditorModeEditorModeCommands::FYHEditorModeEditorModeCommands()
	: TCommands<FYHEditorModeEditorModeCommands>("YHEditorModeEditorMode",
		NSLOCTEXT("YHEditorModeEditorMode", "YHEditorModeEditorModeCommands", "YHEditorMode Editor Mode"),
		NAME_None,
		FEditorStyle::GetStyleSetName())
{
}

void FYHEditorModeEditorModeCommands::RegisterCommands()
{
	TArray <TSharedPtr<FUICommandInfo>>& ToolCommands = Commands.FindOrAdd(NAME_Default);

	UI_COMMAND(SimpleTool, "Show Actor Info", "Opens message box with info about a clicked actor", EUserInterfaceActionType::Button, FInputChord());
	ToolCommands.Add(SimpleTool);

	UI_COMMAND(InteractiveTool, "Measure Distance", "Measures distance between 2 points (click to set origin, shift-click to set end point)", EUserInterfaceActionType::ToggleButton, FInputChord());
	ToolCommands.Add(InteractiveTool);

	//----YHEM----
	UI_COMMAND(YHTool, "YHTool", "YHTool", EUserInterfaceActionType::Button, FInputChord());
	ToolCommands.Add(YHTool);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FYHEditorModeEditorModeCommands::GetCommands()
{
	return FYHEditorModeEditorModeCommands::Get().Commands;
}

#undef LOCTEXT_NAMESPACE
