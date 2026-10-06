#include "Gameplay/RunnerVerification.h"
#include "Engine/World.h"
#include "Gameplay/RunnerCharacter.h"
#include "Gameplay/RunnerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformMisc.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
ARunnerVerification::ARunnerVerification() { PrimaryActorTick.bCanEverTick=true; PrimaryActorTick.TickGroup=TG_PrePhysics; }
void ARunnerVerification::Check(const TCHAR* Name,bool bPass)
{
 bFailed|=!bPass;
 Results+=FString::Printf(TEXT("%s,%s\n"),Name,bPass?TEXT("PASS"):TEXT("FAIL"));
 UE_LOG(LogTemp,Display,TEXT("WEEK3_TEST %s %s"),Name,bPass?TEXT("PASS"):TEXT("FAIL"));
}
void ARunnerVerification::Finish()
{
 Results+=FString::Printf(TEXT("RunDistance,%.3f\nTapApex,%.3f\nHoldApex,%.3f\nOverall,%s\n"),Distance,TapApex,Apex,bFailed?TEXT("FAIL"):TEXT("PASS"));
 IFileManager::Get().MakeDirectory(*(FPaths::ProjectSavedDir()/TEXT("Verification")),true);
 FFileHelper::SaveStringToFile(Results,*(FPaths::ProjectSavedDir()/TEXT("Verification/Week03.csv")));
 FPlatformMisc::RequestExitWithStatus(false,bFailed?1:0);
}
void ARunnerVerification::Tick(float Dt)
{
 Super::Tick(Dt);
 auto* PC=Cast<ARunnerController>(GetWorld()->GetFirstPlayerController());
 auto* C=PC?Cast<ARunnerCharacter>(PC->GetPawn()):nullptr;
 Time+=Dt;
 if (!C) { if(Time>15) { Check(TEXT("PossessedRunner"),false); Finish(); } return; }
 auto* Sub=PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
 auto Inject=[&](UInputAction* Action,FInputActionValue Value) { Sub->InjectInputForAction(Action,Value,{},{}); };
 if (Phase==0 && Time>2)
 {
  
  Check(TEXT("PossessedRunner"),true); Check(TEXT("MappingInstalled"),Sub->HasMappingContext(C->GameplayContext));
  Check(TEXT("Grounded"),C->GetCharacterMovement()->IsMovingOnGround());
  const bool bBaseline=FParse::Param(FCommandLine::Get(),TEXT("LabBaseline"));
  Check(bBaseline?TEXT("FloorProbeLeftForLab"):TEXT("FloorProbe"),bBaseline?!C->ProbeFloor():C->ProbeFloor());
  StartX=C->GetActorLocation().X; Time=0; Phase=1;
 }
 else if(Phase==1)
 {
  Inject(C->MoveAction,FInputActionValue(1.f));
  if(Time>=3)
  {
   Distance=StartX-C->GetActorLocation().X;
   Check(TEXT("ThreeSecondRun"),Distance>335 && Distance<375);
   Check(TEXT("PlaneY"),FMath::Abs(C->GetActorLocation().Y)<0.1f);
   Check(TEXT("PickupCollected"),PC->Pickups==1);
   C->GetCharacterMovement()->StopMovementImmediately(); Time=0; Phase=2;
  }
 }
 else if(Phase==2)
 {
  Inject(C->MoveAction,FInputActionValue(1.f));
  if(Time>3)
  {
   Check(TEXT("WallBlocks"),C->GetActorLocation().X>=17.5f && C->GetActorLocation().X<25.f);
   C->SetActorLocation(FVector(500,0,34)); C->GetCharacterMovement()->StopMovementImmediately();Time=0;Phase=3;
  }
 }
 else if(Phase==3 && Time>0.5f) { StartZ=C->GetActorLocation().Z;Apex=0;Time=0;Phase=4; }
 else if(Phase==4 || Phase==6)
 {
  const float Hold=Phase==4?0.033f:0.20f;
  // Injection exercises Started and Completed bindings, not direct jump calls.
  if(Time<=Hold+Dt) Inject(C->JumpAction,FInputActionValue(true));
  Apex=FMath::Max(Apex,C->GetActorLocation().Z-StartZ);
  if(Time>1.4f)
  {
   if(Phase==4) { TapApex=Apex;Time=0;Phase=5; }
   else { const bool bBaseline=FParse::Param(FCommandLine::Get(),TEXT("LabBaseline")); Check(bBaseline?TEXT("BasicJumpWithHoldLeftForLab"):TEXT("VariableHeightJump"),bBaseline?(TapApex>5.f && Apex>5.f && FMath::Abs(Apex-TapApex)<5.f):(Apex>TapApex+8.f));Time=0;Phase=10; }
  }
 }
 else if(Phase==5 && Time>.5f) { Apex=0;Time=0;Phase=6; }
 else if(Phase==10)
 {
  // Capture only after timed movement/jump trials; screenshot readback can stall a frame.
  if(FParse::Param(FCommandLine::Get(),TEXT("Week03Capture")))
  {
   IFileManager::Get().MakeDirectory(*(FPaths::ProjectSavedDir()/TEXT("Verification")),true);
   FScreenshotRequest::RequestScreenshot(FPaths::ProjectSavedDir()/TEXT("Verification/Arena.png"),false,false);
  }
  Time=0;Phase=11;
 }
 else if(Phase==11 && Time>1.f) { Time=0;Phase=7; }
 else if(Phase==7)
 {
  if(FParse::Param(FCommandLine::Get(),TEXT("LabBaseline")))
  {
   PC->ToggleMenu(); Check(TEXT("MenuLeftForLab"),!PC->bMenuOpen && Sub->HasMappingContext(C->GameplayContext));
   PC->RestartRunner(); Time=0; Phase=9; return;
  }
  PC->ToggleMenu(); StartX=C->GetActorLocation().X;
  Check(TEXT("MenuRemovesContext"),!Sub->HasMappingContext(C->GameplayContext));
  C->BeginJump();Time=0;Phase=8;
 }
 else if(Phase==8)
 {
  
  if(Time>.2f && !bReleased && FParse::Param(FCommandLine::Get(),TEXT("Week03Capture")))
  {
   bReleased=true;
   FScreenshotRequest::RequestScreenshot(FPaths::ProjectSavedDir()/TEXT("Verification/Menu.png"),false,false);
  }
  C->ApplyMoveIntent(1.f);
  if(Time>.5f)
  {
   Check(TEXT("MenuBlocksMovement"),FMath::Abs(C->GetActorLocation().X-StartX)<.1f && !C->bPressedJump);
   PC->ToggleMenu();Check(TEXT("ResumeRestoresContext"),Sub->HasMappingContext(C->GameplayContext));
   PC->RestartRunner();Time=0;Phase=9;
  }
 }
 else if(Phase==9 && Time>1)
 {
  Check(TEXT("RespawnRestoresContext"),Sub->HasMappingContext(C->GameplayContext) && C->bGameplayEnabled);
  Finish();
 }
}

