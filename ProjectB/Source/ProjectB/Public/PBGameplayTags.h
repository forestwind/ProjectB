// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace PBGameplayTags
{
	/** Input **/
	PROJECTB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	PROJECTB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	PROJECTB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipSword)
	PROJECTB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipSword)
	
	/** Player **/
	PROJECTB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);
	
	PROJECTB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
	PROJECTB_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Sword);
}
