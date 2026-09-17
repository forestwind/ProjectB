// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PBPawnCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Items/Weapons/PBWeaponBase.h"

void UPBPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, APBWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("%s Tag has already been registered Weapon "), *InWeaponTagToRegister.ToString())
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);
	
	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
}

APBWeaponBase* UPBPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (const TObjectPtr<APBWeaponBase>* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
	{
		return *FoundWeapon;
	}

	return nullptr;
}

APBWeaponBase* UPBPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPBPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EPBToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EPBToggleDamageType::CurrentEquippedWeapon)
	{
		APBWeaponBase* WeaponToToggle =  GetCharacterCurrentEquippedWeapon();
		check(WeaponToToggle);
		
		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			
			OverlappedActors.Empty();
		}
	}
}

void UPBPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPBPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractionActor)
{
}
