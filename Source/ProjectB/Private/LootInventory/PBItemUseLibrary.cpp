// Fill out your copyright notice in the Description page of Project Settings.

#include "LootInventory/PBItemUseLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Engine/GameInstance.h"
#include "LootInventory/PBLIConsumeItemDataAsset.h"
#include "LootInventory/PBLIGameplayTags.h"
#include "Subsystems/LIInventorySubsystem.h"
#include "Subsystems/LIItemSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogPBItemUse, Log, All);

bool UPBItemUseLibrary::UseConsumeItem(AActor* InUser, int32 InItemId, int32 InSlotId)
{
	if (InUser == nullptr)
	{
		return false;
	}

	UAbilitySystemComponent* UserASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InUser);
	UGameInstance* GameInstance = InUser->GetGameInstance();
	if (UserASC == nullptr || GameInstance == nullptr)
	{
		UE_LOG(LogPBItemUse, Warning, TEXT("UseConsumeItem: no ASC or GameInstance (%s)"), *InUser->GetName());
		return false;
	}

	// 소비 타입 확인
	const ULIItemSubsystem* ItemSubsystem = GameInstance->GetSubsystem<ULIItemSubsystem>();
	const FLIItemRowBase* ItemRow = ItemSubsystem->FindItemRow(InItemId);
	if (ItemRow == nullptr || ItemRow->GetItemType() != PBLIGameplayTags::Item_Type_Consume)
	{
		UE_LOG(LogPBItemUse, Warning, TEXT("UseConsumeItem: ItemId %d is not a consume item"), InItemId);
		return false;
	}

	// 소비 리소스로 변환
	const FPBLIConsumeItemAssets* ConsumeAssets = static_cast<const FPBLIConsumeItemAssets*>(ItemSubsystem->FindItemAssets(InItemId));
	if (ConsumeAssets == nullptr)
	{
		UE_LOG(LogPBItemUse, Warning, TEXT("UseConsumeItem: no assets for ItemId %d"), InItemId);
		return false;
	}

	TSubclassOf<UGameplayEffect> UseEffectClass = ConsumeAssets->UseEffect.LoadSynchronous();
	if (UseEffectClass == nullptr)
	{
		UE_LOG(LogPBItemUse, Warning, TEXT("UseConsumeItem: no UseEffect for ItemId %d"), InItemId);
		return false;
	}

	// 1개 제거 후 효과 적용
	ULIInventorySubsystem* Inventory = GameInstance->GetSubsystem<ULIInventorySubsystem>();
	if (!Inventory->RemoveItemFromSlot(InSlotId))
	{
		return false;
	}

	const FGameplayEffectSpecHandle SpecHandle = UserASC->MakeOutgoingSpec(UseEffectClass, 1.0f, UserASC->MakeEffectContext());
	UserASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	UE_LOG(LogPBItemUse, Log, TEXT("Used ItemId %d (SlotId %d)"), InItemId, InSlotId);
	return true;
}