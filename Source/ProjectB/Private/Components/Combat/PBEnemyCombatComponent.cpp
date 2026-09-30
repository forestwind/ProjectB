// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PBEnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "PBGameplayTags.h"

#include "PBDebugHelper.h"

void UPBEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);
	
	bool bIsValidBlock = false;
	
	const bool bIsPlayerBlocking = false;
	const bool bIsMyAttackUnblockable = false;
	
	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		
	}
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	
	
	if (bIsValidBlock)
	{
		
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), PBGameplayTags::Shared_Event_MeleeHit, EventData);
	}
}
