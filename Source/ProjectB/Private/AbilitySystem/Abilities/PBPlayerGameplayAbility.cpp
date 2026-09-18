// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PBPlayerGameplayAbility.h"

#include "Characters/PBPlayerCharacter.h"
#include "Controllers/PBPlayerController.h"
#include "AbilitySystem/PBAbilitySystemComponent.h"
#include "PBGameplayTags.h"

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

FGameplayEffectSpecHandle UPBPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(PBGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}

	return EffectSpecHandle;
}
