// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PBPlayerController.h"

APBPlayerController::APBPlayerController()
{
	PlayerTeamID = FGenericTeamId(0);
}

FGenericTeamId APBPlayerController::GetGenericTeamId() const
{
	return PlayerTeamID;
}
