// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/LIItemDataAsset.h"
#include "PBConsumeItemDataAsset.generated.h"

class UGameplayEffect;
struct FGameplayTag;

// 기획 데이터 (CSV 컬럼이 됨)
USTRUCT(BlueprintType)
struct FPBConsumeItemRow : public FLIItemRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	virtual FGameplayTag GetItemType() const override;
};

// 아이템 리소스 (언리얼 에디터에서 지정해야 될것)                      
USTRUCT(BlueprintType)                                                               
struct FPBConsumeItemAssets : public FLIItemAssetsBase                               
{                                                                                    
	GENERATED_BODY()                                                               
                                                                                       
public:                                                                              
	UPROPERTY(EditAnywhere, BlueprintReadOnly)                                     
	TSoftClassPtr<UGameplayEffect> UseEffect;                                      
};

/**
 * 
 */
UCLASS()
class PROJECTB_API UPBConsumeItemDataAsset : public ULIItemDataAssetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TMap<int32, FPBConsumeItemAssets> Assets;
	
	virtual const FLIItemAssetsBase* FindAssets(int32 InItemId) const override
	{
		return Assets.Find(InItemId);
	}
};
