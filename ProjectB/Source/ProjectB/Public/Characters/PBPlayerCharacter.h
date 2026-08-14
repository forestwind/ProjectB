// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PBBaseCharacter.h"
#include "PBPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class PROJECTB_API APBPlayerCharacter : public APBBaseCharacter
{
	GENERATED_BODY()

public:
	APBPlayerCharacter();
	
private:
	
#pragma region Component

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	
#pragma endregion
	
};
