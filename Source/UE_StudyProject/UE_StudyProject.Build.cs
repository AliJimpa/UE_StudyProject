// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_StudyProject : ModuleRules
{
	public UE_StudyProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"UE_StudyProject",
			"UE_StudyProject/TP_FirstPerson",
			"UE_StudyProject/TP_FirstPerson/Variant_Horror",
			"UE_StudyProject/TP_FirstPerson/Variant_Horror/UI",
			"UE_StudyProject/TP_FirstPerson/Variant_Shooter",
			"UE_StudyProject/TP_FirstPerson/Variant_Shooter/AI",
			"UE_StudyProject/TP_FirstPerson/Variant_Shooter/UI",
			"UE_StudyProject/TP_FirstPerson/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
