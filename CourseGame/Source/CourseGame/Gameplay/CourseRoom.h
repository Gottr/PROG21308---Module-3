#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CourseRoom.generated.h"
class UBoxComponent;
class UPaperSprite;
class UPaperSpriteComponent;
UCLASS(Blueprintable)
class COURSEGAME_API ACourseRoom : public AActor
{
    GENERATED_BODY()
public:
    ACourseRoom();
    virtual void OnConstruction(const FTransform& Transform) override;
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<USceneComponent> Scene;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UBoxComponent> FloorCollision;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UBoxComponent> LeftWallCollision;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UBoxComponent> RightWallCollision;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UPaperSpriteComponent> FloorVisual;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UPaperSpriteComponent> LeftWallVisual;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UPaperSpriteComponent> RightWallVisual;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UPaperSpriteComponent> Background;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UPaperSpriteComponent> Foreground;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Room") TObjectPtr<UPaperSprite> FloorImage;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Room") TObjectPtr<UPaperSprite> BackgroundImage;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Room") TObjectPtr<UPaperSprite> ForegroundImage;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UBoxComponent> PlatformCollision;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TObjectPtr<UPaperSpriteComponent> PlatformVisual;
};
