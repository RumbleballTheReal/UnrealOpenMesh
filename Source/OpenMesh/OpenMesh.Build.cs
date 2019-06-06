// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class OpenMesh : ModuleRules
    {
        public OpenMesh(ReadOnlyTargetRules Target) : base(Target)
        {
            //Needed for Open Mesh Library
            {
                bEnableExceptions = true;
                bUseRTTI = true; // Enable RuntimeTypeInformation
                PublicDefinitions.Add("_USE_MATH_DEFINES");
                PrivateDefinitions.Add("_CRT_SECURE_NO_WARNINGS"); // should disable warning warning C4996, but does not work
            }

            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            string VersionFolder = "Version8_0";

            PublicIncludePaths.AddRange(
                new string[] {
                Path.Combine(ModuleDirectory, VersionFolder, "Public"),
                }
                );

            PrivateIncludePaths.AddRange(
                new string[] {
                Path.Combine(ModuleDirectory, VersionFolder, "Private"),
                    // ... add other private include paths required here ...
                }
                );

            PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "Projects"
            });

        }
    }
}