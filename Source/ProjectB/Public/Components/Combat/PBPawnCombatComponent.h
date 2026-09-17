// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PBPawnExtensionComponentBase.h"
#include "PBPawnCombatComponent.generated.h"

class APBWeaponBase;


UENUM(BlueprintType)
enum class EPBToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand,
};

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
	
	UFUNCTION(BlueprintCallable, Category = "PB|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EPBToggleDamageType ToggleDamageType = EPBToggleDamageType::CurrentEquippedWeapon);
	
	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractionActor);
	
protected:
	UPROPERTY()
	TArray<TObjectPtr<AActor>> OverlappedActors;
	
	
private:
	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<APBWeaponBase>> CharacterCarriedWeaponMap;
};
