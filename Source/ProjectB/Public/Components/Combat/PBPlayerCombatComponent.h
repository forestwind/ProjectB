// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PBPawnCombatComponent.h"
#include "PBPlayerCombatComponent.generated.h"

class APBPlayerWeapon;
/**
 *
 */
UCLASS()
class PROJECTB_API UPBPlayerCombatComponent : public UPBPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "PB|Combat")
	APBPlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
	
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractionActor) override;
};
