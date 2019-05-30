// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System;
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class ThirdParty : ModuleRules
    {
        public ThirdParty(ReadOnlyTargetRules Target) : base(Target)
        {
            // File existence helps to populate ThirdParty directory into Visual Studio when generating project files
        }
    }
}