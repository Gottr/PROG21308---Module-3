#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Week03AssetLibrary.generated.h"
class UInputMappingContext;
class UInputAction;
UCLASS()
class COURSEGAMEEDITOR_API UWeek03AssetLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable) static void ConfigureMapping(UInputMappingContext* Context,UInputAction* Move,UInputAction* Jump);
};
