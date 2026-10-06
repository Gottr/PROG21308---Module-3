#include "Week03AssetLibrary.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputModifiers.h"
void UWeek03AssetLibrary::ConfigureMapping(UInputMappingContext* Context,UInputAction* Move,UInputAction* Jump)
{
    if (!Context || !Move || !Jump) return;
    Context->UnmapAll();
    for (const FKey Key:{EKeys::A,EKeys::Left})
    {
        auto& Mapping=Context->MapKey(Move,Key);
        Mapping.Modifiers.Add(NewObject<UInputModifierNegate>(Context));
    }
    Context->MapKey(Move,EKeys::D); Context->MapKey(Move,EKeys::Right);
    auto& Stick=Context->MapKey(Move,EKeys::Gamepad_LeftX);
    auto* Deadzone=NewObject<UInputModifierDeadZone>(Context); Deadzone->LowerThreshold=0.15f;
    Stick.Modifiers.Add(Deadzone);
    Context->MapKey(Jump,EKeys::SpaceBar); Context->MapKey(Jump,EKeys::Gamepad_FaceButton_Bottom);
    Context->MarkPackageDirty();
}
