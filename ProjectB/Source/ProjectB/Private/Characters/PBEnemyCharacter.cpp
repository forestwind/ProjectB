// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PBEnemyCharacter.h"

#include "Components/Combat/PBEnemyCombatComponent.h"
#include "DataAssets/StartUpData/PBEnemyStartUpData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"

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
