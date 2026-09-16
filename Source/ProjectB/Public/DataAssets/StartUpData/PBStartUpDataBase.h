// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PBStartUpDataBase.generated.h"

class UPBAbilitySystemComponent;
class UPBGameplayAbility;
/**
 * 
 */
UCLASS()
class PROJECTB_API UPBStartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveToAbilitySystemComponent(UPBAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UPBGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UPBGameplayAbility>> ReactiveAbilities;
	
	void GrantAbilities(const TArray<TSubclassOf<UPBGameplayAbility>>& InAbilitiesToGive,UPBAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
