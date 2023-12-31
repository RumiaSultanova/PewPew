// Pew-Pew Game. All Rights Reserved.

using UnrealBuildTool;

public class PewPew : ModuleRules
{
	public PewPew(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new[]
		{
			"PewPew/Public/Player",
			"PewPew/Public/Components",
			"PewPew/Public/Dev",
			"PewPew/Public/Weapon",
			"PewPew/Public/UI",
			"PewPew/Public/Animations",
			"PewPew/Public/Pickups"
		});
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
