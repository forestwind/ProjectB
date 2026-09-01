// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/PBInputConfig.h"
#include "PBDebugHelper.h"
#include "PBInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTB_API UPBInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserObject, class CallbackFunc>
	void BindNativeInputAction(const UPBInputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);

	template <class UserObject, class CallbackFunc>
	void BindAbilityInputAction(const UPBInputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);
};

template <class UserObject, class CallbackFunc>
void UPBInputComponent::BindNativeInputAction(const UPBInputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data is Null"));

	if (UInputAction* FoundNativeInputAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundNativeInputAction, TriggerEvent, ContextObject, Func);
	}
	else
	{
		Debug::Log(FString::Printf(TEXT("BindNativeInputAction: No native input action found for tag %s in %s"), *InInputTag.ToString(), *InInputConfig->GetName()), FColor::Yellow, -1, ELogVerbosity::Warning);
	}
}

template <class UserObject, class CallbackFunc>
void UPBInputComponent::BindAbilityInputAction(const UPBInputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data is Null"));

	for (const FPBInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;
		{
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, AbilityInputActionConfig.InputTag);
		}
	}
}
