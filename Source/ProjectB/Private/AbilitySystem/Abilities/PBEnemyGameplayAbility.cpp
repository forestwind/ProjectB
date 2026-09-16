// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PBEnemyGameplayAbility.h"

#include "Characters/PBEnemyCharacter.h"

APBEnemyCharacter* UPBEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedPbEnemyCharacter.IsValid())
	{
		CachedPbEnemyCharacter = Cast<APBEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPbEnemyCharacter.Get();
}

UPBEnemyCombatComponent* UPBEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
