// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AICoreStyle.h"

class FAICoreCommands : public TCommands<FAICoreCommands>
{
public:

	FAICoreCommands()
		: TCommands<FAICoreCommands>(TEXT("AICore"), NSLOCTEXT("Contexts", "AICore", "AICore Plugin"), NAME_None, FAICoreStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};