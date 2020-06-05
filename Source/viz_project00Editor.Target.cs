// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class viz_project00EditorTarget : TargetRules
{
	public viz_project00EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        //PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "DesktopPlatform" });
		ExtraModuleNames.AddRange( new string[] { "viz_project00", "Core", "CoreUObject", "Engine", "InputCore", "DesktopPlatform" } );
	}
}
