#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class FTestYHCommands : public TCommands<FTestYHCommands>
{
public:
	FTestYHCommands();

	// TCommands interface
	virtual void RegisterCommands() override;
public:
	TSharedPtr<FUICommandInfo> CommandA;
};
