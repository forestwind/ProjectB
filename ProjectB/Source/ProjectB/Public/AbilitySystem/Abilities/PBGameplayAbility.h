// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PBGameplayAbility.generated.h"

class UPBPawnCombatComponent;
class UPBAbilitySystemComponent;

UENUM(BlueprintType)
enum class EPBAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven,
};

/**
 * 
 */
UCLASS()
class PROJECTB_API UPBGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface.
	
	UPROPERTY(EditDefaultsOnly, Category = "PBAbility")
	EPBAbilityActivationPolicy AbilityActivationPolicy = EPBAbilityActivationPolicy::OnTriggered;
	
	UFUNCTION(BlueprintPure, Category = "PBAbility")
	UPBPawnCombatComponent* GetPBPawnCombatComponentFromActorInfo() const;
	
	UFUNCTION(BlueprintPure, Category = "PBAbility")
	UPBAbilitySystemComponent* GetPBAbilitySystemComponentFromActorInfo() const;
};
