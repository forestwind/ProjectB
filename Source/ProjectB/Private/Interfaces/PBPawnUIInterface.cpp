// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/PBPawnUIInterface.h"

// Add default functionality here for any IPBPawnUIInterface functions that are not pure virtual.
UPBPlayerUIComponent* IPBPawnUIInterface::GetPBPlayerUIComponent() const
{
	return nullptr;
}

UPBEnemyUIComponent* IPBPawnUIInterface::GetPBEnemyUIComponent() const
{
	return nullptr;
}
