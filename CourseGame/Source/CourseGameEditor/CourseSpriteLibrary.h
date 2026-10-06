#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CourseSpriteLibrary.generated.h"
class UTexture2D;
class UPaperSprite;
UCLASS()
class UCourseSpriteLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Course|Editor")
    static UPaperSprite* CreateSpriteAsset(UTexture2D* Texture, const FString& PackagePath, bool FeetPivot);
};
