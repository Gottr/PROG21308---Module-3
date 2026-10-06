#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RunnerVerification.generated.h"
UCLASS()
class COURSEGAME_API ARunnerVerification : public AActor
{
 GENERATED_BODY()
public:
 ARunnerVerification();
 virtual void Tick(float DeltaSeconds) override;
private:
 int32 Phase=0;
 float Time=0,StartX=0,Distance=0,Apex=0,TapApex=0,StartZ=0;
 bool bReleased=false,bFailed=false;
 FString Results;
 void Check(const TCHAR* Name,bool bPass);
 void Finish();
};
