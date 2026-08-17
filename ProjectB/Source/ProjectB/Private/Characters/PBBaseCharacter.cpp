// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PBBaseCharacter.h"

#include "AbilitySystem/PBAbilitySystemComponent.h"
#include "AbilitySystem/PBAttributeSet.h"

APBBaseCharacter::APBBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	PBAbilitySystemComponent = CreateDefaultSubobject<UPBAbilitySystemComponent>(TEXT("PBAbilitySystemComponent"));
	PBAttributeSet = CreateDefaultSubobject<UPBAttributeSet>(TEXT("PBAttributeSet"));
}

UAbilitySystemComponent* APBBaseCharacter::GetAbilitySystemComponent() const
{
	return PBAbilitySystemComponent;
}

void APBBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (PBAbilitySystemComponent)
	{
		PBAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}
