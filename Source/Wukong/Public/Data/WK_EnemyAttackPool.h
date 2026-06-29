// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WK_EnemyAttackPool.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemyAttackData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag CoolDownTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MinDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Weight;
};



UCLASS()
class WUKONG_API UWK_EnemyAttackPool : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FEnemyAttackData> AttackPool;
};
