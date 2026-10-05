// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "LIStructTypes.generated.h"

class UTexture2D;

/* ───────── 행 구조체 (DataTable Row) ───────── */

// 아이템 행 기반
USTRUCT(BlueprintType)
struct LOOTINVENTORY_API FLIItemRowBase : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemId = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "LI.Item.Rarity"))
	FGameplayTag Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxStack = 1;

	// 행 구조체별 아이템 타입 태그
	virtual FGameplayTag GetItemType() const { return FGameplayTag(); }
};

// 샘플 타입 행
USTRUCT(BlueprintType)
struct LOOTINVENTORY_API FLISampleItemRow : public FLIItemRowBase
{
	GENERATED_BODY()

public:
	virtual FGameplayTag GetItemType() const override;
};

/* ───────── 리소스 구조체 (DataAsset 맵 값) ───────── */

// 아이템 리소스 기반
USTRUCT(BlueprintType)
struct LOOTINVENTORY_API FLIItemAssetsBase
{
	GENERATED_BODY()

public:
	virtual ~FLIItemAssetsBase() = default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Icon;
};

// 샘플 타입 리소스
USTRUCT(BlueprintType)
struct LOOTINVENTORY_API FLISampleItemAssets : public FLIItemAssetsBase
{
	GENERATED_BODY()
};
