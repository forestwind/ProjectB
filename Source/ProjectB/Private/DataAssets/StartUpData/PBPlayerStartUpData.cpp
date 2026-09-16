// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/PBPlayerStartUpData.h"

#include "AbilitySystem/PBAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/PBGameplayAbility.h"

void UPBPlayerStartUpData::GiveToAbilitySystemComponent(UPBAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FPBPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
