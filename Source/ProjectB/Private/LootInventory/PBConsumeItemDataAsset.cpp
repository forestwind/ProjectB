// Fill out your copyright notice in the Description page of Project Settings.


#include "LootInventory/PBConsumeItemDataAsset.h"
#include "LootInventory/PBLIGameplayTags.h"

FGameplayTag FPBConsumeItemRow::GetItemType() const
{
	return PBLIGameplayTags::Item_Type_Consume;
}