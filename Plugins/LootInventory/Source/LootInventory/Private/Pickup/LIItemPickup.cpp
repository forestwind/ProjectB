// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup/LIItemPickup.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/GameInstance.h"
#include "Subsystems/LIInventorySubsystem.h"

ALIItemPickup::ALIItemPickup()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupSphere"));
	PickupSphere->InitSphereRadius(50.f);

	// OverlapAllDynamic: 막지 않고 겹침만 감지
	PickupSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SetRootComponent(PickupSphere);
}

void ALIItemPickup::BeginPlay()
{
	Super::BeginPlay();

	// 구체에 무언가 닿으면 HandleBeginOverlap 호출
	PickupSphere->OnComponentBeginOverlap.AddDynamic(this, &ALIItemPickup::HandleBeginOverlap);

	// 레벨에 직접 배치한 경우 디테일 패널 값으로 겉모습 갱신
	OnItemSet();
}

void ALIItemPickup::SetItem(int32 InItemId, int32 InCount)
{
	ItemId = InItemId;
	Count = InCount;
}

void ALIItemPickup::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bPickedUp)
	{
		return;
	}

	// 플레이어가 조종하는 폰만
	const APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn == nullptr || !Pawn->IsPlayerControlled())
	{
		return;
	}

	ULIInventorySubsystem* Inventory = GetGameInstance()->GetSubsystem<ULIInventorySubsystem>();
	if (!Inventory->AddItem(ItemId, Count))
	{
		// 아이템 추가 실패 (없는 ItemId 등)
		return;
	}

	bPickedUp = true;
	OnPickedUp();
	Destroy();
}
