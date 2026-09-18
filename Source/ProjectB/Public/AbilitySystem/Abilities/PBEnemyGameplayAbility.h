// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/PBGameplayAbility.h"
#include "PBEnemyGameplayAbility.generated.h"

class UPBEnemyCombatComponent;
class APBEnemyCharacter;
/**
 * 
 */
UCLASS()
class PROJECTB_API UPBEnemyGameplayAbility : public UPBGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "PB|Ability")
	APBEnemyCharacter* GetPBEnemyCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "PB|Ability")
	UPBEnemyCombatComponent* GetPBEnemyCombatComponentFromActorInfo();
	
private:
	TWeakObjectPtr<APBEnemyCharacter> CachedPbEnemyCharacter;
};
