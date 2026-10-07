// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/PBBaseCharacter.h"
#include "GameplayTagContainer.h"
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

	// LootInventory 드롭 그룹 (0이면 드롭 없음, BP 기본값 + 레벨에 배치한 적마다 변경 가능)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot")
	int32 DropGroupId = 0;

private:
	void InitEnemyStartUpData();

	// 사망 태그(Shared.Status.Dead)가 붙으면 드롭
	void OnDeadTagChanged(const FGameplayTag InTag, int32 TagCount);

public:
	FORCEINLINE UPBEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
	FORCEINLINE int32 GetDropGroupId() const { return DropGroupId; }
};
