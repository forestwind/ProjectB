// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/PBGEExecCalc_DamageTaken.h"
#include "AbilitySystem/PBAttributeSet.h"
#include "PBGameplayTags.h"

#include "PBDebugHelper.h"

struct FPBDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FPBDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPBAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPBAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPBAttributeSet, DamageTaken, Target, false);
	}
};

static const FPBDamageCapture& GetPBDamageCapture()
{
	static FPBDamageCapture PBDamageCapture;
	return PBDamageCapture;
}

UPBGEExecCalc_DamageTaken::UPBGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetPBDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetPBDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetPBDamageCapture().DamageTakenDef);
}

void UPBGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPBDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	
	float BaseDamage = 0.0f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(PBGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(PBGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(PBGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
		}
	}

	float TargetDefensePower = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPBDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	
	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.0f;

		BaseDamage *= DamageIncreasePercentLight;
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = (UsedHeavyAttackComboCount * 0.15f) + 1.0f;

		BaseDamage *= DamageIncreasePercentHeavy;
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	Debug::Log_Float(TEXT("FinalDamageDone"), FinalDamageDone);
	
	if (FinalDamageDone > 0.0f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(GetPBDamageCapture().DamageTakenProperty, EGameplayModOp::Override, FinalDamageDone)
		);
	}
}
