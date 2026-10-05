// Fill out your copyright notice in the Description page of Project Settings.


#include "LootInventory/PBLIConsumeItemDataAsset.h"
#include "LootInventory/PBLIGameplayTags.h"

FGameplayTag FPBLIConsumeItemRow::GetItemType() const
{
	return PBLIGameplayTags::Item_Type_Consume;
}
