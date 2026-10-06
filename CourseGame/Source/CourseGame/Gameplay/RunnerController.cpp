#include "Gameplay/RunnerController.h"
#include "Engine/World.h"
#include "Gameplay/RunnerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Engine/LocalPlayer.h"
#include "EngineUtils.h"
#include "Camera/CameraActor.h"
#include "GameFramework/GameModeBase.h"
ARunnerController::ARunnerController() { bAutoManageActiveCameraTarget=false; }
void ARunnerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    // Controller shortcuts survive removal of the gameplay mapping context.
    InputComponent->BindKey(EKeys::Tab,IE_Pressed,this,&ARunnerController::ToggleMenu);
    InputComponent->BindKey(EKeys::Gamepad_Special_Right,IE_Pressed,this,&ARunnerController::ToggleMenu);
    InputComponent->BindKey(EKeys::R,IE_Pressed,this,&ARunnerController::RestartRunner);
    InputComponent->BindKey(EKeys::F,IE_Pressed,this,&ARunnerController::ToggleProbe);
}
void ARunnerController::RemoveInputContext()
{
    if (auto* LP=GetLocalPlayer())
        if (auto* Subsystem=LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            if (InstalledContext) Subsystem->RemoveMappingContext(InstalledContext);
    InstalledContext=nullptr;
    FlushPressedKeys();
}
void ARunnerController::RefreshInputContext()
{
    auto* Runner=Cast<ARunnerCharacter>(GetPawn());
    // OnPossess and AcknowledgePossession can both notify the same local player.
    // Keep one installation instead of flushing and rebuilding it twice.
    if (IsLocalController() && Runner && Runner->bGameplayEnabled
        && InstalledContext && InstalledContext==Runner->GameplayContext)
        if (auto* LP=GetLocalPlayer())
            if (auto* Subsystem=LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
                if (Subsystem->HasMappingContext(InstalledContext)) return;
    RemoveInputContext();
    if (!IsLocalController() || !Runner) return;
    // LAB 2: account for menu ownership before enabling the pawn/installing its context.
    Runner->SetGameplayEnabled(true);
    if (!Runner->GameplayContext) return;
    if (auto* LP=GetLocalPlayer())
        if (auto* Subsystem=LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            FModifyContextOptions Options; Options.bIgnoreAllPressedKeysUntilRelease=true;
            InstalledContext=Runner->GameplayContext;
            Subsystem->AddMappingContext(InstalledContext,0,Options);
            UE_LOG(LogTemp,Display,TEXT("WEEK3_CONTEXT_INSTALLED: %s"),*GetNameSafe(InstalledContext.Get()));
        }
}
void ARunnerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn); RefreshInputContext();
    for (TActorIterator<ACameraActor> It(GetWorld());It;++It) { SetViewTarget(*It); break; }
}
void ARunnerController::AcknowledgePossession(APawn* InPawn) { Super::AcknowledgePossession(InPawn); RefreshInputContext(); }
void ARunnerController::OnUnPossess()
{
    if (auto* Runner=Cast<ARunnerCharacter>(GetPawn())) Runner->SetGameplayEnabled(false);
    RemoveInputContext(); Super::OnUnPossess();
}
void ARunnerController::EndPlay(const EEndPlayReason::Type Reason) { RemoveInputContext(); Super::EndPlay(Reason); }
void ARunnerController::ToggleMenu()
{
    // LAB 2: transfer control to/from the menu using bMenuOpen.
    // Update context lifetime, clear held input, gate the pawn, and set cursor/input mode.
    // The HUD panel and Tab shortcut are supplied. Do not pause the world.
    // A replacement pawn must also respect menu ownership.
}
void ARunnerController::RestartRunner()
{
    if (!HasAuthority()) return;
    APawn* Old=GetPawn(); UnPossess(); if (Old) Old->Destroy();
    if (auto* Mode=GetWorld()->GetAuthGameMode()) Mode->RestartPlayer(this);
}
void ARunnerController::ToggleProbe()
{
    if (auto* Runner=Cast<ARunnerCharacter>(GetPawn())) Runner->bShowFloorProbe=!Runner->bShowFloorProbe;
}

