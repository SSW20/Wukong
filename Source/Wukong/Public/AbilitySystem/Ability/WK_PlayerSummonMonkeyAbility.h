// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WK_PlayerGameplayAbility.h"
#include "WK_PlayerSummonMonkeyAbility.generated.h"

/**
 * 
 */
UCLASS()
class WUKONG_API UWK_PlayerSummonMonkeyAbility : public UWK_PlayerGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SummonCount = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SummonSpread = 180.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<APawn>> SummonPawns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SummonMaxDistance = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SummonMinDistance = 300.f;
};
