#include "Gameplay/CourseGameMode.h"
#include "Engine/World.h"
#include "Engine/GameViewportClient.h"
#include "HAL/PlatformMisc.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Misc/Paths.h"
#include "TimerManager.h"
ACourseGameMode::ACourseGameMode() { DefaultPawnClass = nullptr; }
void ACourseGameMode::StartPlay()
{
    Super::StartPlay();
    // Instructor verification only; normal classroom play never auto-exits.
    if (FParse::Param(FCommandLine::Get(), TEXT("CourseVerify")))
    {
        FTimerHandle CaptureHandle;
        GetWorldTimerManager().SetTimer(CaptureHandle, [] {
            FScreenshotRequest::RequestScreenshot(FPaths::ProjectSavedDir() / TEXT("Screenshots/CourseVerification.png"), false, false);
        }, 2.f, false);
        FTimerHandle ExitHandle;
        GetWorldTimerManager().SetTimer(ExitHandle, [] { FPlatformMisc::RequestExit(false); }, 5.f, false);
    }
}