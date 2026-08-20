// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/PBStartUpDataBase.h"
#include "AbilitySystem/PBAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/PBGameplayAbility.h"

void UPBStartUpDataBase::GiveToAbilitySystemComponent(UPBAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UPBStartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UPBGameplayAbility>>& InAbilitiesToGive, UPBAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UPBGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
