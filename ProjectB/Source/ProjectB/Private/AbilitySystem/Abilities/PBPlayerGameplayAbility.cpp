// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PBPlayerGameplayAbility.h"

#include "Characters/PBPlayerCharacter.h"
#include "Controllers/PBPlayerController.h"

APBPlayerCharacter* UPBPlayerGameplayAbility::GetPBPlayerCharacterFromActorInfo()
{
	if (!CachedPBPlayerCharacter.IsValid())
	{
		CachedPBPlayerCharacter = Cast<APBPlayerCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPBPlayerCharacter.Get();
}

APBPlayerController* UPBPlayerGameplayAbility::GetPBPlayerControllerFromActorInfo()
{
	if (!CachedPBPlayerController.IsValid())
	{
		CachedPBPlayerController = Cast<APBPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedPBPlayerController.Get();
}

UPBPlayerCombatComponent* UPBPlayerGameplayAbility::GetPBPlayerCombatComponentFromActorInfo()
{
	return GetPBPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}
