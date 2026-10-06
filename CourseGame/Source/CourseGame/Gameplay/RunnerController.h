#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RunnerController.generated.h"
class UInputMappingContext;
UCLASS()
class COURSEGAME_API ARunnerController : public APlayerController
{
    GENERATED_BODY()
public:
    ARunnerController();
    virtual void SetupInputComponent() override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void OnUnPossess() override;
    virtual void AcknowledgePossession(APawn* InPawn) override;
    virtual void EndPlay(const EEndPlayReason::Type Reason) override;
    void ToggleMenu();
    void RestartRunner();
    UPROPERTY(BlueprintReadOnly) bool bMenuOpen=false;
    UPROPERTY(BlueprintReadOnly) int32 Pickups=0;
private:
    void RefreshInputContext();
    void RemoveInputContext();
    void ToggleProbe();
    UPROPERTY() TObjectPtr<UInputMappingContext> InstalledContext;
};
