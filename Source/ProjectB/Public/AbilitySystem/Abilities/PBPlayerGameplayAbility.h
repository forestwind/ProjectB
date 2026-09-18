// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PBGameplayAbility.h"
#include "PBPlayerGameplayAbility.generated.h"

class UPBPlayerCombatComponent;
class APBPlayerController;
class APBPlayerCharacter;
/**
 * 
 */
UCLASS()
class PROJECTB_API UPBPlayerGameplayAbility : public UPBGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "PBAbility")
	APBPlayerCharacter* GetPBPlayerCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "PBAbility")
	APBPlayerController* GetPBPlayerControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "PBAbility")
	UPBPlayerCombatComponent* GetPBPlayerCombatComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "PBAbility")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);
	
private:
	TWeakObjectPtr<APBPlayerCharacter> CachedPBPlayerCharacter;
	TWeakObjectPtr<APBPlayerController> CachedPBPlayerController;
};
