// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "PBGEExecCalc_DamageTaken.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTB_API UPBGEExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UPBGEExecCalc_DamageTaken();
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
