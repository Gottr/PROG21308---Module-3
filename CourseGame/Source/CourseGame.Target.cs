using UnrealBuildTool;
using System.Collections.Generic;
public class CourseGameTarget : TargetRules
{
    public CourseGameTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        ExtraModuleNames.Add("CourseGame");
    }
}