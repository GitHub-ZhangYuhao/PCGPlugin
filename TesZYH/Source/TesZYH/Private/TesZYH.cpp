// Copyright Epic Games, Inc. All Rights Reserved.

#include "TesZYH.h"
#include "TestYHCommands.h"

#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#define LOCTEXT_NAMESPACE "FTesZYHModule"



void FTesZYHModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//FTestYHCommands : public TCommands<FTestYHCommands> 继承自TCommands有注册函数，用来注册命令 ，通常在模块的启动函数中调用。观察它的实现可看到内部调用了RegisterCommands函数。
	FTestYHCommands::Register();

	//在Startup Module中 创建 FUICommandList
	PluginCommandList = MakeShareable(new FUICommandList);
	//为 命令映射操作
	PluginCommandList->MapAction(
		FTestYHCommands::Get().CommandA ,
		FExecuteAction::CreateRaw(this , &FTesZYHModule::CommandAAction) ,
		FCanExecuteAction() );
	
	// 获取关卡编辑器模块
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	// 扩展关卡编辑器的菜单
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension(
			"WindowLayout",
			EExtensionHook::After,
			PluginCommandList ,
			FMenuExtensionDelegate::CreateLambda( [] (FMenuBuilder& MenuBuilder)
			{
				MenuBuilder.AddMenuEntry(FTestYHCommands::Get().CommandA);
			} ) );
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	// 扩展关卡编辑器的工具栏
	{
		TSharedPtr<FExtender> ToolBarExtender = MakeShareable(new FExtender());
		ToolBarExtender->AddToolBarExtension(
			"Settings",
			EExtensionHook::After,
			PluginCommandList ,
			FToolBarExtensionDelegate::CreateLambda( [] (FToolBarBuilder& ToolBarBuilder)
			{
				ToolBarBuilder.AddToolBarButton(FTestYHCommands::Get().CommandA);
			} ) );
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolBarExtender);
	}
	
}

void FTesZYHModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	//使用此方法可以清理命令集使用的任何资源。通常在ShutdownModule()中完成 ,定义在Unregister中
	FTestYHCommands::Unregister();
}

void FTesZYHModule::CommandAAction()
{
	FMessageDialog::Open(EAppMsgType::Ok , FText::FromString(" Exectute Command A ") );
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTesZYHModule, TesZYH)