// Copyright Epic Games, Inc. All Rights Reserved.

#include "AICoreCommands.h"

#define LOCTEXT_NAMESPACE "FAICoreModule"

void FAICoreCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "AICore", "Bring up AICore window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
