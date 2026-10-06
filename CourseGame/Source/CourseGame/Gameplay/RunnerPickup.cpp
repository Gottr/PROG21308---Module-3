#include "Gameplay/RunnerPickup.h"
#include "Gameplay/RunnerCharacter.h"
#include "Gameplay/RunnerController.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
ARunnerPickup::ARunnerPickup()
{
    Trigger=CreateDefaultSubobject<USphereComponent>(TEXT("Trigger")); SetRootComponent(Trigger);
    Trigger->SetSphereRadius(12.f);
    Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
    Trigger->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
    Trigger->SetGenerateOverlapEvents(true);
    Trigger->OnComponentBeginOverlap.AddDynamic(this,&ARunnerPickup::Collect);
    Visual=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual")); Visual->SetupAttachment(Trigger);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Engine/BasicShapes/Sphere"));
    Visual->SetStaticMesh(Mesh.Object); Visual->SetRelativeScale3D(FVector(.16f));
    Visual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
void ARunnerPickup::Collect(UPrimitiveComponent*,AActor* Other,UPrimitiveComponent*,int32,bool,const FHitResult&)
{
    auto* Runner=Cast<ARunnerCharacter>(Other);
    auto* PC=Runner?Cast<ARunnerController>(Runner->GetController()):nullptr;
    if (!HasAuthority() || !PC) return;
    ++PC->Pickups; SetActorEnableCollision(false); Destroy();
}
