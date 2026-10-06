#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeaconTestStimulus.generated.h"
// Explicit instructor fixture: production beacons never charge themselves in BeginPlay.
UCLASS()
class COURSEGAME_API ABeaconTestStimulus : public AActor
{
    GENERATED_BODY()
public:
    ABeaconTestStimulus();
protected:
    virtual void BeginPlay() override;
private:
    void RunChecks();
};