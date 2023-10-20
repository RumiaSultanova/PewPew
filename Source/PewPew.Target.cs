// Pew-Pew Game. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PewPewTarget : TargetRules
{
	public PewPewTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "PewPew" } );
	}
}
