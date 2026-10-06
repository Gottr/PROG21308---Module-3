#include "Gameplay/BeaconTestStimulus.h"
#include "Gameplay/CourseBeacon.h"
#include "CourseGame.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "TimerManager.h"
ABeaconTestStimulus::ABeaconTestStimulus() { PrimaryActorTick.bCanEverTick = false; }
void ABeaconTestStimulus::BeginPlay()
{
    Super::BeginPlay();
    // Wait until all actors have initialized their configured charge.
    GetWorldTimerManager().SetTimerForNextTick(this, &ABeaconTestStimulus::RunChecks);
}
void ABeaconTestStimulus::RunChecks()
{
    for (TActorIterator<ACourseBeacon> It(GetWorld()); It; ++It)
    {
        const float Before = It->GetCharge();
        It->AddCharge(-10.f);
        const bool bNegativeIgnored = It->GetCharge() == Before;
        It->AddCharge(125.f);
        const bool bClamped = It->GetCharge() == 100.f;
        UE_LOG(LogCourseGame, Display, TEXT("M01 %s: negative=%s oversized=%s charge=%.2f"),
            *It->GetName(), bNegativeIgnored ? TEXT("PASS") : TEXT("FAIL"),
            bClamped ? TEXT("PASS") : TEXT("FAIL"), It->GetCharge());
    }
}