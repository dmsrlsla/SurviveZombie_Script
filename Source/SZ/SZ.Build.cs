// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class SZ : ModuleRules
{
	public SZ(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","OnlineSubsystem", "OnlineSubsystemUtils", "Slate", "SlateCore", "UMG","NavigationSystem" });

		PrivateDependencyModuleNames.AddRange(new string[] { "SZResourceSetting" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore","UMG" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add();

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
