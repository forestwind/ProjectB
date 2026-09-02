// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PBStructTypes.generated.h"

class UPBPlayerLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FPBPlayerWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPBPlayerLinkedAnimLayer> WeaponAnimLayerToLink;
};