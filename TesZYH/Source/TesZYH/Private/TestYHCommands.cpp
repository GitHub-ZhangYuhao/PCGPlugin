#include "TestYHCommands.h"

#define LOCTEXT_NAMESPACE "TestYHCommands"

FTestYHCommands::FTestYHCommands()
	:TCommands<FTestYHCommands>(	//定义UI显示的名称，help提示，Parent , 和 图标
		"TestYHCommands",
		NSLOCTEXT("Contexts", "TestYHCommands", "TestYHCommands"),
		NAME_None,
		FName(*FString("todo")) )
{
}

void FTestYHCommands::RegisterCommands()
{
	//RegisterCommands中将使用UI_COMMAND宏注册自己所有命令。留意最后一个参数，现在是FInputGesture()，它和快捷键有关。 如： FInputChord( EModifierKey::Control, EKeys::H )，表示Ctrl+H
	
	UI_COMMAND(CommandA, "TestZYHCommandA", "Execute ZYH CommandA", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE