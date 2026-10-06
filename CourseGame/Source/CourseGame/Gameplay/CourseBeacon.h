#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CourseBeacon.generated.h"
class UStaticMeshComponent;
class UMaterialInterface;
UCLASS(Blueprintable)
class COURSEGAME_API ACourseBeacon : public AActor
{
    GENERATED_BODY()
public:
    ACourseBeacon();
    UFUNCTION(BlueprintPure, Category="Beacon") float GetCharge() const { return Charge; }
    UFUNCTION(BlueprintCallable, Category="Beacon") void AddCharge(float Amount);
    UFUNCTION(BlueprintImplementableEvent, Category="Beacon") void OnChargeChanged(float NewCharge);
protected:
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Beacon") TObjectPtr<UStaticMeshComponent> Mesh;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Beacon", meta=(ClampMin="0", ClampMax="100")) float InitialCharge = 0.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Beacon") TObjectPtr<UMaterialInterface> VisualMaterial;
private:
    // The lesson fixes the charge interval at 0..100. Editor metadata alone cannot enforce it.
    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Beacon", meta=(AllowPrivateAccess="true")) float Charge = 0.f;
};