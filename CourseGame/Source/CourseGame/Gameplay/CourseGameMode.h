#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CourseGameMode.generated.h"
UCLASS()
class COURSEGAME_API ACourseGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    ACourseGameMode();
    virtual void StartPlay() override;
};