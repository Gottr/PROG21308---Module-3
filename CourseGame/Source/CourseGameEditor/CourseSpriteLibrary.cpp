#include "CourseSpriteLibrary.h"
#include "Engine/Texture2D.h"
#include "PaperSprite.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/PackageName.h"
#include "UObject/Package.h"
UPaperSprite* UCourseSpriteLibrary::CreateSpriteAsset(UTexture2D* Texture, const FString& PackagePath, bool FeetPivot)
{
    if (!Texture || !FPackageName::IsValidLongPackageName(PackagePath)) return nullptr;
    UPackage* Package = CreatePackage(*PackagePath);
    UPaperSprite* Sprite = NewObject<UPaperSprite>(Package, *FPackageName::GetLongPackageAssetName(PackagePath), RF_Public | RF_Standalone);
    FSpriteAssetInitParameters Params; Params.SetTextureAndFill(Texture); Params.SetPixelsPerUnrealUnit(1.f);
    Sprite->InitializeSprite(Params);
    Sprite->SetPivotMode(FeetPivot ? ESpritePivotMode::Bottom_Center : ESpritePivotMode::Center_Center, FVector2D::ZeroVector);
    FAssetRegistryModule::AssetCreated(Sprite); Sprite->MarkPackageDirty();
    return Sprite;
}
