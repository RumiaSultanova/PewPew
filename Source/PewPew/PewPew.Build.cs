// Pew-Pew Game. All Rights Reserved.

using UnrealBuildTool;

public class PewPew : ModuleRules
{
	public PewPew(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Niagara",
			"PhysicsCore",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new[]
		{
			"PewPew/Public/Player",
			"PewPew/Public/Components",
			"PewPew/Public/Dev",
			"PewPew/Public/Weapon",
			"PewPew/Public/UI",
			"PewPew/Public/Animations",
			"PewPew/Public/Pickups",
			"PewPew/Public/Weapon/Components",
			"PewPew/Public/AI",
			"PewPew/Public/AI/Services",
			"PewPew/Public/AI/EQS"
		});
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
