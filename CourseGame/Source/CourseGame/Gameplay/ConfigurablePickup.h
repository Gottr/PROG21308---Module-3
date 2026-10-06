#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConfigurablePickup.generated.h"
class UStaticMeshComponent;
UCLASS(Blueprintable)
class COURSEGAME_API AConfigurablePickup : public AActor
{
    GENERATED_BODY()
public:
    AConfigurablePickup();
    UFUNCTION(BlueprintPure, Category="Pickup") int32 GetScoreValue() const { return ScoreValue; }
    UFUNCTION(BlueprintCallable, Category="Pickup") bool ValidateConfiguration() const;
protected:
    virtual void BeginPlay() override;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup") TObjectPtr<UStaticMeshComponent> Mesh;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pickup") int32 ScoreValue = 10;
};