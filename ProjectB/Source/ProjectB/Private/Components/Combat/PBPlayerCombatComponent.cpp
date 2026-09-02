// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PBPlayerCombatComponent.h"

#include "Items/Weapons/PBPlayerWeapon.h"

APBPlayerWeapon* UPBPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<APBPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
