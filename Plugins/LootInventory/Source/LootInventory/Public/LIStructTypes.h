// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LIStructTypes.generated.h"

// 공용 구조체

// 인벤토리 한 칸
USTRUCT(BlueprintType)
struct LOOTINVENTORY_API FLIInventoryEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 ItemId = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Count = 0;
};
