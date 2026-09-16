// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/PBStartUpDataBase.h"
#include "PBEnemyStartUpData.generated.h"

class UPBEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class PROJECTB_API UPBEnemyStartUpData : public UPBStartUpDataBase
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UPBAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UPBEnemyGameplayAbility>> EnemyCombatAbilities;
};
