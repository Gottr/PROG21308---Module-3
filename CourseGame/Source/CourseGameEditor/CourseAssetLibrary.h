#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CourseAssetLibrary.generated.h"
class UBlueprint;
UCLASS()
class UCourseAssetLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Course|Editor") static bool CanActorEverTick(AActor* Actor);
    UFUNCTION(BlueprintCallable, Category="Course|Editor")
    static bool AddBeaconPresentation(UBlueprint* Blueprint);
};