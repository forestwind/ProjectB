// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LIStructTypes.h"
#include "LIItemDataAsset.generated.h"

// 아이템 리소스 데이터 기반 (ItemId → 리소스 구조체 맵)
UCLASS(Abstract, BlueprintType)
class LOOTINVENTORY_API ULIItemDataAssetBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual const FLIItemAssetsBase* FindAssets(int32 InItemId) const { return nullptr; }
};

UCLASS()
class LOOTINVENTORY_API ULISampleItemDataAsset : public ULIItemDataAssetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TMap<int32, FLISampleItemAssets> Assets;

	virtual const FLIItemAssetsBase* FindAssets(int32 InItemId) const override { return Assets.Find(InItemId); }
};
