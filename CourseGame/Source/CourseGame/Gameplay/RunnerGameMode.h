#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunnerGameMode.generated.h"
UCLASS()
class COURSEGAME_API ARunnerGameMode : public AGameModeBase
{
    GENERATED_BODY()
public: ARunnerGameMode();
    virtual void StartPlay() override;
};
