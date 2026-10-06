#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RunnerPickup.generated.h"
class USphereComponent;
class UStaticMeshComponent;
UCLASS()
class COURSEGAME_API ARunnerPickup : public AActor
{
    GENERATED_BODY()
public: ARunnerPickup();
private:
    UPROPERTY(VisibleAnywhere) TObjectPtr<USphereComponent> Trigger;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> Visual;
    UFUNCTION() void Collect(UPrimitiveComponent* Overlapped,AActor* Other,UPrimitiveComponent* OtherComp,int32 Index,bool bSweep,const FHitResult& Hit);
};
