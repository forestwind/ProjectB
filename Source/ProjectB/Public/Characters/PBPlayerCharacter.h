// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PBBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "PBPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPBInputConfig;
struct FInputActionValue;
class UPBPlayerCombatComponent;
/**
 *
 */
UCLASS()
class PROJECTB_API APBPlayerCharacter : public APBBaseCharacter
{
	GENERATED_BODY()

public:
	APBPlayerCharacter();

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
#pragma region Component

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPBPlayerCombatComponent> PlayerCombatComponent;
#pragma endregion


#pragma region Input

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="CharacterData", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPBInputConfig> InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
	
#pragma endregion

public:
	FORCEINLINE UPBPlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponent; }
};
