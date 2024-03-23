// Copyright Epic Games, Inc. All Rights Reserved.

#include "YHEditorModeEditorModeToolkit.h"
#include "YHEditorModeEditorMode.h"
#include "Engine/Selection.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "YHEditorModeEditorModeToolkit"

FYHEditorModeEditorModeToolkit::FYHEditorModeEditorModeToolkit()
{
}

void FYHEditorModeEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FYHEditorModeEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FYHEditorModeEditorModeToolkit::GetToolkitFName() const
{
	return FName("YHEditorModeEditorMode");
}

FText FYHEditorModeEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "YHEditorModeEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE
