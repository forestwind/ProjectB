// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "PBBaseCharacter.generated.h"

class UPBAttributeSet;
class UPBAbilitySystemComponent;

UCLASS()
class PROJECTB_API APBBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APBBaseCharacter();
	
	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	//~ End IAbilitySystemInterface Interface
	
protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UPBAbilitySystemComponent> PBAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UPBAttributeSet> PBAttributeSet;
	
public:
	
	FORCEINLINE UPBAbilitySystemComponent* GetPBAbilitySystemComponent() const { return PBAbilitySystemComponent; }
	FORCEINLINE UPBAttributeSet* GetPBAttributeSet() const { return PBAttributeSet; }
};
