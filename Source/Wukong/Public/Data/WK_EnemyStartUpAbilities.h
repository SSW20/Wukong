// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WK_StartUpAbilities.h"
#include "WK_EnemyStartUpAbilities.generated.h"

/**
 * 
 */
UCLASS()
class WUKONG_API UWK_EnemyStartUpAbilities : public UWK_StartUpAbilities
{
	GENERATED_BODY()

public:
	virtual void GrantAbilityToActorASC(UWK_AbilitySystemComponent* WKAbilitySystemComponent, float Level) override;

	UPROPERTY(EditDefaultsOnly, Category="StartUp")
	TArray<TSubclassOf<UWK_GameplayAbility>> EnemyStartUpAbilities;
};
