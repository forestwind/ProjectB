// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PBItemUseLibrary.generated.h"

// 아이템 사용
UCLASS()
class PROJECTB_API UPBItemUseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// 소비 아이템 1개 사용 (UseEffect 적용)
	UFUNCTION(BlueprintCallable, Category = "LootInventory")
	static bool UseConsumeItem(AActor* InUser, int32 InItemId, int32 InSlotId);
};