using UnrealBuildTool;
public class CourseGameEditor : ModuleRules
{
    public CourseGameEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivateDependencyModuleNames.AddRange(new[] {
            "EnhancedInput", "InputCore", "Core", "CoreUObject", "Engine", "CourseGame", "Paper2D", "UnrealEd",
            "BlueprintGraph", "Kismet", "KismetCompiler", "AssetRegistry"
        });
    }
}