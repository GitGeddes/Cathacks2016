// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cathacks2016 : ModuleRules
{
	public Cathacks2016(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D" });
        PublicIncludePaths.AddRange(new string[] { "Paper2D/Classes" });
	}
}
