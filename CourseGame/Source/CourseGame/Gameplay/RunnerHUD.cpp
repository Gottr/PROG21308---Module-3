#include "Gameplay/RunnerHUD.h"
#include "Gameplay/RunnerController.h"
#include "Gameplay/RunnerCharacter.h"
#include "Engine/Canvas.h"
void ARunnerHUD::DrawHUD()
{
    Super::DrawHUD();
    if (!Canvas) return;
    auto* PC=Cast<ARunnerController>(GetOwningPlayerController());
    if (!PC) return;
    DrawRect(FLinearColor(0,0,0,0.8f),0,0,Canvas->SizeX,76);
    DrawText(TEXT("WEEK 3 LAB | A/D: move | Space: jump | R: respawn | TODO: jump release, Tab menu, F probe"),FLinearColor::White,16,12);
    if (auto* Runner=Cast<ARunnerCharacter>(PC->GetPawn()))
        DrawText(FString::Printf(TEXT("Speed %.1f | Y %.2f | Floor probe %s | Pickups %d"),Runner->GetVelocity().Size2D(),Runner->GetActorLocation().Y,Runner->bFloorProbeHit?TEXT("hit"):TEXT("clear"),PC->Pickups),FLinearColor::White,16,38);
    if (PC->bMenuOpen)
    {
        DrawRect(FLinearColor(0.02f,0.03f,0.07f,0.94f),Canvas->SizeX*0.15f,Canvas->SizeY*0.3f,Canvas->SizeX*0.7f,150);
        DrawText(TEXT("MENU - test your gameplay input gate"),FLinearColor::White,Canvas->SizeX*0.2f,Canvas->SizeY*0.3f+30,nullptr,1.5f);
        DrawText(TEXT("Press Tab / controller Menu to resume. Release held keys before moving again."),FLinearColor::White,Canvas->SizeX*0.2f,Canvas->SizeY*0.3f+80);
    }
}
