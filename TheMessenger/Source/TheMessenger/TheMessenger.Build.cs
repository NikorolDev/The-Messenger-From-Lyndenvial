// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheMessenger : ModuleRules
{
	public TheMessenger(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
															"UMG", "LevelSequence", "MovieScene", "MediaAssets", "SlateCore" });
	}
}
