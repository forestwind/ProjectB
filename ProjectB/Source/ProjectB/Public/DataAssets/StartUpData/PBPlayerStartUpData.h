// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAssets/StartUpData/PBStartUpDataBase.h"
#include "PBPlayerStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FPBPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPBGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

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
