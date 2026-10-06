#include "Gameplay/ConfigurablePickup.h"
#include "CourseGame.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
AConfigurablePickup::AConfigurablePickup()
{
    PrimaryActorTick.bCanEverTick = false;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    Mesh->SetStaticMesh(Cube.Object);
    Mesh->SetRelativeScale3D(FVector(0.4f));
}
bool AConfigurablePickup::ValidateConfiguration() const
{
    if (ScoreValue <= 0)
    {
        UE_LOG(LogCourseGame, Error, TEXT("%s: ScoreValue must be positive; got %d. Pickup rejected."), *GetPathName(), ScoreValue);
        return false;
    }
    return true;
}
void AConfigurablePickup::BeginPlay()
{
    Super::BeginPlay();
    if (!ValidateConfiguration())
    {
        SetActorEnableCollision(false);
        return;
    }
    UE_LOG(LogCourseGame, Display, TEXT("%s: configured score %d"), *GetName(), ScoreValue);
}