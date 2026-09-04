// Fill out your copyright notice in the Description page of Project Settings.


#include "PBFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/PBAbilitySystemComponent.h"

UPBAbilitySystemComponent* UPBFunctionLibrary::NativeGetPBASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UPBAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UPBFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UPBAbilitySystemComponent* ASC = NativeGetPBASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UPBFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UPBAbilitySystemComponent* ASC = NativeGetPBASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UPBFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UPBAbilitySystemComponent* ASC = NativeGetPBASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UPBFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EPBConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor,TagToCheck) ? EPBConfirmType::Yes : EPBConfirmType::No;
}
