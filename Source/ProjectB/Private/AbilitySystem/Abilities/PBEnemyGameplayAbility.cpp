// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PBEnemyGameplayAbility.h"

#include "PBGameplayTags.h"
#include "AbilitySystem/PBAbilitySystemComponent.h"
#include "Characters/PBEnemyCharacter.h"

APBEnemyCharacter* UPBEnemyGameplayAbility::GetPBEnemyCharacterFromActorInfo()
{
	if (!CachedPbEnemyCharacter.IsValid())
	{
		CachedPbEnemyCharacter = Cast<APBEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPbEnemyCharacter.Get();
}

UPBEnemyCombatComponent* UPBEnemyGameplayAbility::GetPBEnemyCombatComponentFromActorInfo()
{
	return GetPBEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UPBEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
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
	
	EffectSpecHandle.Data->SetSetByCallerMagnitude(PBGameplayTags::Shared_SetByCaller_BaseDamage, InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));
	
	return EffectSpecHandle;
}
