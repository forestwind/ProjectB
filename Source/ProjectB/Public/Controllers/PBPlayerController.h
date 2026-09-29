// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "PBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTB_API APBPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	APBPlayerController();
	
	//~ Begin IGenericTeamAgentInterface Interface.
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface Interface.
	
private:
	UPROPERTY(VisibleAnywhere)
	FGenericTeamId PlayerTeamID;
};
