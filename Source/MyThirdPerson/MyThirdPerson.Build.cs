// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyThirdPerson : ModuleRules
{
	public MyThirdPerson(ReadOnlyTargetRules Target) : base(Target)
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
			"MyThirdPerson",
			"MyThirdPerson/Variant_Platforming",
			"MyThirdPerson/Variant_Platforming/Animation",
			"MyThirdPerson/Variant_Combat",
			"MyThirdPerson/Variant_Combat/AI",
			"MyThirdPerson/Variant_Combat/Animation",
			"MyThirdPerson/Variant_Combat/Gameplay",
			"MyThirdPerson/Variant_Combat/Interfaces",
			"MyThirdPerson/Variant_Combat/UI",
			"MyThirdPerson/Variant_SideScrolling",
			"MyThirdPerson/Variant_SideScrolling/AI",
			"MyThirdPerson/Variant_SideScrolling/Gameplay",
			"MyThirdPerson/Variant_SideScrolling/Interfaces",
			"MyThirdPerson/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
