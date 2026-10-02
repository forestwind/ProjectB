// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LootInventory : ModuleRules
{
	public LootInventory(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		// 우선 전부 Public으로 두고, 헤더에 노출되지 않는 모듈은 나중에 Private으로 옮긴다.
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
