// Copyright Epic Games, Inc. All Rights Reserved.

#include "YHEditorModeEditorMode.h"
#include "YHEditorModeEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "YHEditorModeEditorModeCommands.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "Tools/YHEditorModeSimpleTool.h"
#include "Tools/YHEditorModeInteractiveTool.h"

// step 2: register a ToolBuilder in FYHEditorModeEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "YHEditorModeEditorMode"

const FEditorModeID UYHEditorModeEditorMode::EM_YHEditorModeEditorModeId = TEXT("EM_YHEditorModeEditorMode");

FString UYHEditorModeEditorMode::SimpleToolName = TEXT("YHEditorMode_ActorInfoTool");
FString UYHEditorModeEditorMode::InteractiveToolName = TEXT("YHEditorMode_MeasureDistanceTool");
//----YHEM----
FString UYHEditorModeEditorMode::YHToolName = TEXT("YHEditorMode_YHTool");


UYHEditorModeEditorMode::UYHEditorModeEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UYHEditorModeEditorMode::EM_YHEditorModeEditorModeId,
		LOCTEXT("ModeName", "YHEditorMode"),
		FSlateIcon(),
		true);
}


UYHEditorModeEditorMode::~UYHEditorModeEditorMode()
{
}


void UYHEditorModeEditorMode::ActorSelectionChangeNotify()
{
}

void UYHEditorModeEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FYHEditorModeEditorModeCommands& SampleToolCommands = FYHEditorModeEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UYHEditorModeSimpleToolBuilder>(this));
	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UYHEditorModeInteractiveToolBuilder>(this));
	//----YHEM----
	RegisterTool(SampleToolCommands.YHTool, YHToolName, NewObject<UYHEditorModeYHITlBuilder>(this));
	
	
	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
}

void UYHEditorModeEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FYHEditorModeEditorModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UYHEditorModeEditorMode::GetModeCommands() const
{
	return FYHEditorModeEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
