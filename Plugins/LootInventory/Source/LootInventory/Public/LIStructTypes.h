// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "LIStructTypes.generated.h"

class UTexture2D;

/* ───────── 행 구조체 (CSV → DataTable, 기획 데이터) ───────── */

// 모든 아이템 행의 기반
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

	// 타입은 행 구조체가 결정 (CSV 컬럼 아님)
	virtual FGameplayTag GetItemType() const { return FGameplayTag(); }
};

// 샘플 타입. 새 타입은 이 구조체처럼 FLIItemRowBase를 상속하고 전용 필드를 추가한다
USTRUCT(BlueprintType)
struct LOOTINVENTORY_API FLISampleItemRow : public FLIItemRowBase
{
	GENERATED_BODY()

public:
	virtual FGameplayTag GetItemType() const override;
};

/* ───────── 에셋 구조체 (에디터에서 지정, 리소스 참조) ───────── */

// 모든 아이템 리소스의 기반
USTRUCT(BlueprintType)
struct LOOTINVENTORY_API FLIItemAssetsBase
{
	GENERATED_BODY()

public:
	virtual ~FLIItemAssetsBase() = default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Icon;
};

// 샘플 타입 리소스. 전용 리소스는 이 구조체처럼 FLIItemAssetsBase를 상속해 추가한다
USTRUCT(BlueprintType)
struct LOOTINVENTORY_API FLISampleItemAssets : public FLIItemAssetsBase
{
	GENERATED_BODY()
};
