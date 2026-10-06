// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LILootSettings.generated.h"

class ULIItemDataAssetBase;

// Config/DefaultGame.ini에 저장
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Loot Inventory"))
class LOOTINVENTORY_API ULILootSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	// Project Settings 안의 분류 → "Plugins" 아래에 표시
	virtual FName GetCategoryName() const override { return TEXT("Plugins"); }

	// 타입별 묶음 DataAsset 목록 (DA_ItemConsume 등)
	UPROPERTY(Config, EditAnywhere, Category = "Item")
	TArray<TSoftObjectPtr<ULIItemDataAssetBase>> ItemDataAssets;
};