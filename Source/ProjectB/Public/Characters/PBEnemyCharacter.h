// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PBBaseCharacter.h"
#include "PBEnemyCharacter.generated.h"

class UWidgetComponent;
class UPBEnemyUIComponent;
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
	
	//~ Begin IPBPawnUIInterface Interface.
	virtual UPBPawnUIComponent* GetPBPawnUIComponent() const override;
	virtual UPBEnemyUIComponent* GetPBEnemyUIComponent() const override;
	//~ End IPBPawnUIInterface Interface
	
protected:
	
	virtual void BeginPlay() override;
	
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UPBEnemyCombatComponent> EnemyCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UPBEnemyUIComponent> EnemyUIComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent;

private:
	void InitEnemyStartUpData();
	
public:
	FORCEINLINE UPBEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
