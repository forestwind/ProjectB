// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/PBCharacterAnimInstance.h"
#include "PBPlayerAnimInstance.generated.h"

class APBPlayerCharacter;
/**
 * 
 */
UCLASS()
class PROJECTB_API UPBPlayerAnimInstance : public UPBCharacterAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Reference")
	TObjectPtr<APBPlayerCharacter> OwningPlayerCharacter;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 5.0f;
	
	float IdleElapsedTime;
};
