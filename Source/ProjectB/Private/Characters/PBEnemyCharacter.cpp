// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PBEnemyCharacter.h"

#include "Components/WidgetComponent.h"
#include "Components/Combat/PBEnemyCombatComponent.h"
#include "Components/UI/PBEnemyUIComponent.h"
#include "DataAssets/StartUpData/PBEnemyStartUpData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"
#include "Widgets/PBWidgetBase.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "PBGameplayTags.h"
#include "Subsystems/LILootSubsystem.h"

APBEnemyCharacter::APBEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;

	EnemyCombatComponent = CreateDefaultSubobject<UPBEnemyCombatComponent>("EnemyCombatComponent");

	EnemyUIComponent = CreateDefaultSubobject<UPBEnemyUIComponent>("EnemyUIComponent");

	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyHealthWidgetComponent");
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

UPBPawnCombatComponent* APBEnemyCharacter::GetPBPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPBPawnUIComponent* APBEnemyCharacter::GetPBPawnUIComponent() const
{
	return EnemyUIComponent;
}

UPBEnemyUIComponent* APBEnemyCharacter::GetPBEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void APBEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (UPBWidgetBase* HealthWidget = Cast<UPBWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}

	// 드롭 그룹이 있는 경우만 이벤트 등록
	if (DropGroupId != 0)
	{
		// RegisterGameplayTagEvent: 이 태그의 갯수 변경시 알림
		GetAbilitySystemComponent()->RegisterGameplayTagEvent(PBGameplayTags::Shared_Status_Dead, EGameplayTagEventType::NewOrRemoved)
			.AddUObject(this, &ThisClass::OnDeadTagChanged);
	}
}

void APBEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void APBEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UPBStartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(PBAbilitySystemComponent);
				}
			}
		)
	);
}

void APBEnemyCharacter::OnDeadTagChanged(const FGameplayTag InTag, int32 TagCount)
{
	if (TagCount <= 0)
	{
		return;
	}

	// 발밑 위치
	const FVector FootLocation = GetActorLocation() - FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());

	// 플러그인 드롭 서브시스템에 그룹 번호와 위치만 넘김 (굴림 → 픽업 생성은 플러그인이 처리)
	ULILootSubsystem* Loot = GetGameInstance()->GetSubsystem<ULILootSubsystem>();
	Loot->DropLoot(GetWorld(), DropGroupId, FootLocation);
}
