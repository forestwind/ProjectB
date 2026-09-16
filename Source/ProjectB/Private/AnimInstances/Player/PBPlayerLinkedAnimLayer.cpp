// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/PBPlayerLinkedAnimLayer.h"

#include "AnimInstances/Player/PBPlayerAnimInstance.h"

UPBPlayerAnimInstance* UPBPlayerLinkedAnimLayer::GetPlayerAnimInstance() const
{
	return Cast<UPBPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
