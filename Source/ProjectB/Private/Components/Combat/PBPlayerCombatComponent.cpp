// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PBPlayerCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Items/Weapons/PBPlayerWeapon.h"
#include "PBGameplayTags.h"

#include "PBDebugHelper.h"

APBPlayerWeapon* UPBPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<APBPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UPBPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Super::OnHitTargetActor(HitActor);

	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), PBGameplayTags::Shared_Event_MeleeHit, Data);
}

void UPBPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractionActor)
{
	Super::OnWeaponPulledFromTargetActor(InteractionActor);
}
