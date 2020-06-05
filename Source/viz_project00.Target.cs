// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class viz_project00Target : TargetRules
{
	public viz_project00Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        //PublicDependency.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });
		//PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		ExtraModuleNames.AddRange( new string[] { "viz_project00", "Core", "CoreUObject", "Engine", "InputCore", "DesktopPlatform" } );
	}
}
