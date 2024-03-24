// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestPreviewViewport.h"
#include "TestPreviewViewportStyle.h"
#include "TestPreviewViewportCommands.h"
#include "LevelEditor.h"
#include "STestEditorViewport.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName TestPreviewViewportTabName("TestPreviewViewport");

#define LOCTEXT_NAMESPACE "FTestPreviewViewportModule"

void FTestPreviewViewportModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FTestPreviewViewportStyle::Initialize();
	FTestPreviewViewportStyle::ReloadTextures();

	FTestPreviewViewportCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FTestPreviewViewportCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FTestPreviewViewportModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FTestPreviewViewportModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TestPreviewViewportTabName, FOnSpawnTab::CreateRaw(this, &FTestPreviewViewportModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FTestPreviewViewportTabTitle", "TestPreviewViewport"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FTestPreviewViewportModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FTestPreviewViewportStyle::Shutdown();

	FTestPreviewViewportCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TestPreviewViewportTabName);
}

TSharedRef<SDockTab> FTestPreviewViewportModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FTestPreviewViewportModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("TestPreviewViewport.cpp"))
		);

	return SNew(SDockTab)
	.TabRole(ETabRole::NomadTab)
	[
		// Put your tab content here!
		SNew(STestEditorViewport)
	];
	
	/*return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];*/
}

void FTestPreviewViewportModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(TestPreviewViewportTabName);
}

void FTestPreviewViewportModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FTestPreviewViewportCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FTestPreviewViewportCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestPreviewViewportModule, TestPreviewViewport)