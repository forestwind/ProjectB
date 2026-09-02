// Fill out your copyright notice in the Description page of Project Settings.


#include "PBStructTypes.h"

#include "AbilitySystem/Abilities/PBGameplayAbility.h"

bool FPBPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
