#include "Gameplay/CourseBeacon.h"
#include "CourseGame.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
ACourseBeacon::ACourseBeacon()
{
    PrimaryActorTick.bCanEverTick = false;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    Mesh->SetStaticMesh(Cube.Object);
}
void ACourseBeacon::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    if (VisualMaterial) Mesh->SetMaterial(0, VisualMaterial);
}
void ACourseBeacon::BeginPlay()
{
    Super::BeginPlay();
    if (!FMath::IsFinite(InitialCharge) || InitialCharge < 0.f || InitialCharge > 100.f)
        UE_LOG(LogCourseGame, Warning, TEXT("%s: invalid InitialCharge; sanitizing to 0..100"), *GetName());
    Charge = FMath::IsFinite(InitialCharge) ? FMath::Clamp(InitialCharge, 0.f, 100.f) : 0.f;
    UE_LOG(LogCourseGame, Display, TEXT("%s: initial charge %.2f"), *GetName(), Charge);
}
void ACourseBeacon::AddCharge(float Amount)
{
    if (!FMath::IsFinite(Amount) || Amount <= 0.f) return;
    const float OldCharge = Charge;
    Charge += FMath::Min(Amount, 100.f - Charge);
    if (Charge != OldCharge) OnChargeChanged(Charge);
}