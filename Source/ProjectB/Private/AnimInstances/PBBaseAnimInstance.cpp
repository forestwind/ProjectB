// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/PBBaseAnimInstance.h"


#include "PBFunctionLibrary.h"

bool UPBBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UPBFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
