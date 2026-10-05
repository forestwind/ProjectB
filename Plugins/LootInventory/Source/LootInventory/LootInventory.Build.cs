// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LootInventory : ModuleRules
{
	public LootInventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"GameplayTags",
				"GameplayAbilities",
				"DeveloperSettings",
				"UMG",
				"Slate",
				"SlateCore",
				"EnhancedInput",
			}
			);
	}
}
