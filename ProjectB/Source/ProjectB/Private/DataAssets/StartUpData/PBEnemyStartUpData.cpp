// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/PBEnemyStartUpData.h"

#include "AbilitySystem/PBAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/PBEnemyGameplayAbility.h"

void UPBEnemyStartUpData::GiveToAbilitySystemComponent(UPBAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UPBEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;
			
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			
			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
