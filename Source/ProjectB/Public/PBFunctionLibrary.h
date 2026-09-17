// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "PBEnumTypes.h"
#include "PBFunctionLibrary.generated.h"

class UPBAbilitySystemComponent;
class UPBPawnCombatComponent;

/**
 * 
 */
UCLASS()
class PROJECTB_API UPBFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UPBAbilitySystemComponent* NativeGetPBASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category ="PB|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category ="PB|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category ="PB|FunctionLibrary", meta=(DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EPBConfirmType& OutConfirmType);
	
	static UPBPawnCombatComponent* NativeGetPBPawnCombatComponentFromActor(AActor* InActor);
	
	UFUNCTION(BlueprintCallable, Category ="PB|FunctionLibrary", meta=(DisplayName = "Get PB Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPBPawnCombatComponent* BP_GetPBPawnCombatComponentFromActor(AActor* InActor, EPBValidType& OutValidType);
};
