// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PBEnemyCharacter.h"

#include "Components/WidgetComponent.h"
#include "Components/Combat/PBEnemyCombatComponent.h"
#include "Components/UI/PBEnemyUIComponent.h"
#include "DataAssets/StartUpData/PBEnemyStartUpData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"
#include "Widgets/PBWidgetBase.h"

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
