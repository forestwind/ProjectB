// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PBWidgetBase.h"

#include "Components/UI/PBEnemyUIComponent.h"
#include "Interfaces/PBPawnUIInterface.h"

void UPBWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (IPBPawnUIInterface* PawnUIInterface = Cast<IPBPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UPBPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPBPlayerUIComponent())
		{
			BP_OnOwningPBPlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}

void UPBWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (IPBPawnUIInterface* PawnUIInterface = Cast<IPBPawnUIInterface>(OwningEnemyActor))
	{
		UPBEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetPBEnemyUIComponent();
		
		checkf(EnemyUIComponent,TEXT("Failed to extrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());
		
		BP_OnOwningPBEnemyUIComponentInitialized(EnemyUIComponent);
			
	}
}
