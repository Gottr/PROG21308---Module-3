#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RunnerHUD.generated.h"
UCLASS()
class COURSEGAME_API ARunnerHUD : public AHUD
{
    GENERATED_BODY()
public: virtual void DrawHUD() override;
};
