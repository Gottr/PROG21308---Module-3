#pragma once
#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "InputActionValue.h"
#include "RunnerCharacter.generated.h"
class UInputAction;
class UInputMappingContext;
class UPaperFlipbook;
UCLASS(Blueprintable)
class COURSEGAME_API ARunnerCharacter : public APaperCharacter
{
    GENERATED_BODY()
public:
    ARunnerCharacter();
    virtual void Tick(float DeltaSeconds) override;
    virtual void SetupPlayerInputComponent(UInputComponent* Input) override;
    UFUNCTION(BlueprintCallable) void SetGameplayEnabled(bool bEnabled);
    UFUNCTION(BlueprintCallable) bool ProbeFloor();
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input") TObjectPtr<UInputAction> MoveAction;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input") TObjectPtr<UInputAction> JumpAction;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input") TObjectPtr<UInputMappingContext> GameplayContext;
    UPROPERTY(EditDefaultsOnly, Category="Animation") TObjectPtr<UPaperFlipbook> IdleAnimation;
    UPROPERTY(EditDefaultsOnly, Category="Animation") TObjectPtr<UPaperFlipbook> RunAnimation;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Diagnostics") bool bGameplayEnabled = true;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Diagnostics") bool bFloorProbeHit = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Diagnostics") bool bShowFloorProbe = false;
    // Deliberately incorrect comparison mode for the guided activity. Off by default.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Diagnostics") bool bDemonstrateDeltaTimeBug = false;
    void ApplyMoveIntent(float Value);
    void BeginJump();
    void EndJump();
private:
    void Move(const FInputActionValue& Value);
    void ReleaseMove(const FInputActionValue& Value);
};
