using UnrealBuildTool;
using System.Collections.Generic;
public class CourseGameEditorTarget : TargetRules
{
    public CourseGameEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        ExtraModuleNames.AddRange(new[] { "CourseGame", "CourseGameEditor" });
    }
}