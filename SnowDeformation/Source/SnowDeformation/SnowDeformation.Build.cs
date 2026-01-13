// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SnowDeformation : ModuleRules
{
	public SnowDeformation(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate",
			"DeformationPlugin",
			"DeformationCompute",
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"SnowDeformation",
			"SnowDeformation/Variant_Platforming",
			"SnowDeformation/Variant_Platforming/Animation",
			"SnowDeformation/Variant_Combat",
			"SnowDeformation/Variant_Combat/AI",
			"SnowDeformation/Variant_Combat/Animation",
			"SnowDeformation/Variant_Combat/Gameplay",
			"SnowDeformation/Variant_Combat/Interfaces",
			"SnowDeformation/Variant_Combat/UI",
			"SnowDeformation/Variant_SideScrolling",
			"SnowDeformation/Variant_SideScrolling/AI",
			"SnowDeformation/Variant_SideScrolling/Gameplay",
			"SnowDeformation/Variant_SideScrolling/Interfaces",
			"SnowDeformation/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
