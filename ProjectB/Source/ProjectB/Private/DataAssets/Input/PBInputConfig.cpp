// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/PBInputConfig.h"

UInputAction* UPBInputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FPBInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}