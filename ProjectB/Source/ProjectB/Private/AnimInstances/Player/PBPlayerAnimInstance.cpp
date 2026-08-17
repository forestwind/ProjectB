// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/PBPlayerAnimInstance.h"

#include "Characters/PBPlayerCharacter.h"

void UPBPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningPlayerCharacter = Cast<APBPlayerCharacter>(OwningCharacter);
	}
}

void UPBPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	
	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.0f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}
}
