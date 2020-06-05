// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class viz_project00 : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    public viz_project00(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        LoadHDF5Library(Target);

        LoadProceduralMeshComponent();
    }

    public bool LoadHDF5Library(ReadOnlyTargetRules Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string LibrariesPath = Path.Combine(ThirdPartyPath, "hdf5", "lib");

            /*
            test your path with:
            using System; // Console.WriteLine("");
            Console.WriteLine("... LibrariesPath -> " + LibrariesPath);
            */

            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libhdf5.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libhdf5_cpp.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libhdf5_hl.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libhdf5_hl_cpp.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libhdf5_tools.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libszip.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libzlib.lib"));
        }

        if (isLibrarySupported)
        {
            // Include path
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "hdf5", "include"));
        }

        Definitions.Add(string.Format("WITH_BOBS_MAGIC_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }

    public bool LoadProceduralMeshComponent()
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ProceduralMeshComponent" });
        return true;
    }
}
