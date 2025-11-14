// Copyright Epic Games, Inc. All Rights Reserved.

#include "AICoreEditor.h"
#include "AICoreStyle.h"
#include "AICoreCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "MyFactory.h"

static const FName AICoreTabName("AICore");

#define LOCTEXT_NAMESPACE "FAICoreEditorModule"

void FAICoreEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FAICoreStyle::Initialize();
	FAICoreStyle::ReloadTextures();

	FAICoreCommands::Register();

	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAICoreCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FAICoreEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAICoreEditorModule::RegisterMenus));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(AICoreTabName, FOnSpawnTab::CreateRaw(this, &FAICoreEditorModule::OnSpawnPluginTab)).SetDisplayName(LOCTEXT("FAICoreTabTitle", "AICore")).SetMenuType(ETabSpawnerMenuType::Hidden);

	//UBlueprint::MyFactory.Add(UMyFactory::StaticClass());
}

void FAICoreEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAICoreStyle::Shutdown();

	FAICoreCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(AICoreTabName);

	//UBlueprint::MyFactory.Remove(UMyFactory::StaticClass());

}

TSharedRef<SDockTab> FAICoreEditorModule::OnSpawnPluginTab(const FSpawnTabArgs &SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FAICoreEditorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("AICore.cpp")));

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
			[
				// Put your tab content here!
				SNew(SBox)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
						[SNew(STextBlock)
							 .Text(WidgetText)]];
}

void FAICoreEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(AICoreTabName);
}

void FAICoreEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu *Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection &Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAICoreCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu *ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection &Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry &Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAICoreCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FAICoreEditorModule, AICore)