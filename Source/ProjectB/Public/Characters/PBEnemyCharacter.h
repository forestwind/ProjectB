// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PBBaseCharacter.h"
#include "PBEnemyCharacter.generated.h"

class UPBEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class PROJECTB_API APBEnemyCharacter : public APBBaseCharacter
{
	GENERATED_BODY()

public:
	APBEnemyCharacter();

	//~ Begin IPBPawnCombatInterface Interface.
	virtual UPBPawnCombatComponent* GetPBPawnCombatComponent() const override;
	//~ End IPBPawnCombatInterface Interface
	
protected:
	
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UPBEnemyCombatComponent> EnemyCombatComponent;

private:
	void InitEnemyStartUpData();
	
public:
	FORCEINLINE UPBEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
