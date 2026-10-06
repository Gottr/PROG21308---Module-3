#include "Gameplay/RunnerGameMode.h"
#include "Gameplay/RunnerCharacter.h"
#include "Gameplay/RunnerController.h"
#include "Gameplay/RunnerHUD.h"
ARunnerGameMode::ARunnerGameMode()
{
    DefaultPawnClass=ARunnerCharacter::StaticClass();
    PlayerControllerClass=ARunnerController::StaticClass();
    HUDClass=ARunnerHUD::StaticClass();
}

#include "Gameplay/RunnerVerification.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Engine/World.h"
void ARunnerGameMode::StartPlay()
{
    Super::StartPlay();
    if(FParse::Param(FCommandLine::Get(),TEXT("Week03Verify"))) GetWorld()->SpawnActor<ARunnerVerification>();
}
