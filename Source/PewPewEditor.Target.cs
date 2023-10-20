// Pew-Pew Game. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PewPewEditorTarget : TargetRules
{
	public PewPewEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "PewPew" } );
	}
}
