// Fill out your copyright notice in the Description page of Project Settings.


#include "LootInventory/PBLootToastWidget.h"

#include "Engine/GameInstance.h"
#include "TimerManager.h"
#include "Subsystems/LIInventorySubsystem.h"
#include "Subsystems/LIItemSubsystem.h"

namespace
{
	// 타이머 최소 시간 (0 이하면 타이머가 안 돎)
	constexpr float MinTimerSeconds = 0.05f;
}

void UPBLootToastWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (ULIInventorySubsystem* InventorySubsystem = GameInstance->GetSubsystem<ULIInventorySubsystem>())
		{
			InventorySubsystem->OnItemAdded.AddUniqueDynamic(this, &ThisClass::HandleItemAdded);
		}
	}
}

void UPBLootToastWidget::NativeDestruct()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (ULIInventorySubsystem* InventorySubsystem = GameInstance->GetSubsystem<ULIInventorySubsystem>())
		{
			InventorySubsystem->OnItemAdded.RemoveDynamic(this, &ThisClass::HandleItemAdded);
		}
	}

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(ToastTimerHandle);
	}

	PendingToasts.Reset();
	bShowing = false;

	Super::NativeDestruct();
}

void UPBLootToastWidget::HandleItemAdded(int32 ItemId, int32 Count)
{
	FLIInventoryEntry NewToast;
	NewToast.ItemId = ItemId;
	NewToast.Count = Count;
	PendingToasts.Add(NewToast);

	if (!bShowing)
	{
		ShowNext();
	}
}

void UPBLootToastWidget::ShowNext()
{
	ULIItemSubsystem* ItemSubsystem = nullptr;
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		ItemSubsystem = GameInstance->GetSubsystem<ULIItemSubsystem>();
	}

	// 표시 정보 없는 항목은 건너뜀
	while (PendingToasts.Num() > 0)
	{
		const FLIInventoryEntry NextToast = PendingToasts[0];
		PendingToasts.RemoveAt(0);

		FLIItemDisplayInfo Info;
		if (ItemSubsystem && ItemSubsystem->GetItemDisplayInfo(NextToast.ItemId, Info))
		{
			bShowing = true;
			OnShowToast(Info, NextToast.Count);

			GetWorld()->GetTimerManager().SetTimer(ToastTimerHandle, this, &ThisClass::FinishCurrent, FMath::Max(ShowDuration, MinTimerSeconds), false);
			return;
		}
	}

	bShowing = false;
}

void UPBLootToastWidget::FinishCurrent()
{
	OnHideToast();

	GetWorld()->GetTimerManager().SetTimer(ToastTimerHandle, this, &ThisClass::ShowNext, FMath::Max(HideDuration, MinTimerSeconds), false);
}