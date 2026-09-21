// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PBAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "PBFunctionLibrary.h"
#include "PBGameplayTags.h"
#include "Interfaces/PBPawnUIInterface.h"
#include "Components/UI/PBPawnUIComponent.h"
#include "Components/UI/PBPlayerUIComponent.h"
#include "PBDebugHelper.h"

UPBAttributeSet::UPBAttributeSet()
{
	InitCurrentHealth(1.0f);
	InitMaxHealth(1.0f);
	InitCurrentRage(1.0f);
	InitMaxRage(1.0f);
	InitAttackPower(1.0f);
	InitDefensePower(1.0f);
}

void UPBAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPBPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPBPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPBPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPBPawnUIComponent();

	checkf(PawnUIComponent, TEXT("Could not extrac a PBPawnUIComponent form %s "), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.0f, GetMaxRage());

		SetCurrentRage(NewCurrentRage);
		
		if (UPBPlayerUIComponent* PlayerUIComponent = CachedPawnUIInterface->GetPBPlayerUIComponent())
		{
			PlayerUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(
			TEXT("Old Health : %f , Damage Done : %f , NewCurrent Health : %f "),
			OldHealth, DamageDone, NewCurrentHealth);

		Debug::Log(DebugString, FColor::Red);
		
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
		
		if (GetCurrentHealth() == 0.0f)
		{
			UPBFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PBGameplayTags::Shared_Status_Dead);
		}
	}
}
