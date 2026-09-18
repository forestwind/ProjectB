// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PBGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/PBAbilitySystemComponent.h"
#include "Components/Combat/PBPawnCombatComponent.h"

void UPBGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EPBAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UPBGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EPBAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPBPawnCombatComponent* UPBGameplayAbility::GetPBPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPBPawnCombatComponent>();
}

UPBAbilitySystemComponent* UPBGameplayAbility::GetPBAbilitySystemComponentFromActorInfo() const
{
	return Cast<UPBAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UPBGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	
	check(TargetASC && InSpecHandle.IsValid());
	
	return GetPBAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UPBGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EPBSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);
	
	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EPBSuccessType::Successful : EPBSuccessType::Failed;
	
	return ActiveGameplayEffectHandle;
}
