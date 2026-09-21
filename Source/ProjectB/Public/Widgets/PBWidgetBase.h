// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PBWidgetBase.generated.h"

class UPBEnemyUIComponent;
class UPBPlayerUIComponent;
/**
 * 
 */
UCLASS()
class PROJECTB_API UPBWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning PBPlayer UI Component Initialized"))
	void BP_OnOwningPBPlayerUIComponentInitialized(UPBPlayerUIComponent* OwningPlayerUIComponent);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning PBEnemy UI Component Initialized"))
	void BP_OnOwningPBEnemyUIComponentInitialized(UPBEnemyUIComponent* OwningEnemyUIComponent);
	
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
};
