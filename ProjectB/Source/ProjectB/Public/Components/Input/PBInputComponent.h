// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DA_InputConfig.h"
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
	void BindNativeInputAction(const UDA_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
};

template <class UserObject, class CallbackFunc>
void UPBInputComponent::BindNativeInputAction(const UDA_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input config data is Null"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
	else
	{
		Debug::Log(FString::Printf(TEXT("BindNativeInputAction: No native input action found for tag %s in %s"), *InInputTag.ToString(), *InInputConfig->GetName()), FColor::Yellow, -1, ELogVerbosity::Warning);
	}
}
