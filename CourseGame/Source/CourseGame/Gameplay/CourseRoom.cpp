#include "Gameplay/CourseRoom.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"
ACourseRoom::ACourseRoom()
{
    PrimaryActorTick.bCanEverTick = false;
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene")); SetRootComponent(Scene);
    auto Box = [this](const TCHAR* Name, FVector Position, FVector Extent) {
        UBoxComponent* C = CreateDefaultSubobject<UBoxComponent>(Name);
        C->SetupAttachment(Scene); C->SetRelativeLocation(Position); C->SetBoxExtent(Extent);
        C->SetCollisionProfileName(TEXT("BlockAll")); return C;
    };
    FloorCollision = Box(TEXT("FloorCollision"), FVector(320,0,0), FVector(320,32,16));
    LeftWallCollision = Box(TEXT("LeftWallCollision"), FVector(0,0,160), FVector(8,32,160));
    RightWallCollision = Box(TEXT("RightWallCollision"), FVector(640,0,160), FVector(8,32,160));
    auto Art = [this](const TCHAR* Name, FVector Position, FVector Scale) {
        UPaperSpriteComponent* C = CreateDefaultSubobject<UPaperSpriteComponent>(Name);
        C->SetupAttachment(Scene); C->SetRelativeLocation(Position); C->SetRelativeScale3D(Scale);
        C->SetCollisionEnabled(ECollisionEnabled::NoCollision); return C;
    };
    FloorVisual = Art(TEXT("FloorVisual"), FVector(320,0,0), FVector(20,1,1));
    LeftWallVisual = Art(TEXT("LeftWallVisual"), FVector(0,0,160), FVector(0.5f,1,10));
    RightWallVisual = Art(TEXT("RightWallVisual"), FVector(640,0,160), FVector(0.5f,1,10));
    Background = Art(TEXT("Background"), FVector(320,40,180), FVector(20,1,11.25f));
    Foreground = Art(TEXT("Foreground"), FVector(480,-20,48), FVector(1,1,3));
    PlatformCollision = Box(TEXT("PlatformCollision"), FVector(280,0,88), FVector(64,32,8));
    PlatformVisual = Art(TEXT("PlatformVisual"), FVector(280,0,88), FVector(4,1,0.5f));
}
void ACourseRoom::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    FloorVisual->SetSprite(FloorImage); Background->SetSprite(BackgroundImage); Foreground->SetSprite(ForegroundImage);
    LeftWallVisual->SetSprite(FloorImage); RightWallVisual->SetSprite(FloorImage);
    PlatformVisual->SetSprite(FloorImage);
}
