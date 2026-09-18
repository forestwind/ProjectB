// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PBAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "PBFunctionLibrary.h"
#include "PBGameplayTags.h"

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
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);
	}

	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.0f, GetMaxRage());

		SetCurrentRage(NewCurrentRage);
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

		Debug::Log(DebugString,FColor::Red);
		
		if (NewCurrentHealth == 0.0f)
		{
			UPBFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(),PBGameplayTags::Shared_Status_Dead);
		}
	}
}
