// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/PBStartUpDataBase.h"
#include "PBStructTypes.h"
#include "PBPlayerStartUpData.generated.h"

/**
 *
 */
UCLASS()
class PROJECTB_API UPBPlayerStartUpData : public UPBStartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UPBAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FPBPlayerAbilitySet> PlayerStartUpAbilitySets;
};
