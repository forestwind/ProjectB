// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PBPawnExtensionComponentBase.h"
#include "PBPawnCombatComponent.generated.h"

class APBWeaponBase;
/**
 *
 */
UCLASS()
class PROJECTB_API UPBPawnCombatComponent : public UPBPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "PB|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, APBWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "PB|Combat")
	APBWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;
	
	UPROPERTY(BlueprintReadWrite, Category = "PB|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
	UFUNCTION(BlueprintCallable, Category = "PB|Combat")
	APBWeaponBase* GetCharacterCurrentEquippedWeapon() const;
	
private:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<APBWeaponBase>> CharacterCarriedWeaponMap;
};
