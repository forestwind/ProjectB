// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/PBBaseAnimInstance.h"
#include "PBPlayerLinkedAnimLayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTB_API UPBPlayerLinkedAnimLayer : public UPBBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UPBPlayerAnimInstance* GetPlayerAnimInstance() const;
	
};
