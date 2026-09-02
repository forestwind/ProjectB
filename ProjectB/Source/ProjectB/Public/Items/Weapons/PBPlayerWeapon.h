// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/PBWeaponBase.h"
#include "PBStructTypes.h"
#include "PBPlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTB_API APBPlayerWeapon : public APBWeaponBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "WeaponData")
	FPBPlayerWeaponData PlayerWeaponData;
};
