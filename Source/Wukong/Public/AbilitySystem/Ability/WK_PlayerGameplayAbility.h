// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WK_GameplayAbility.h"
#include "Character/Component/Combat/Combo/WK_PlayerComboComponent.h"
#include "WK_PlayerGameplayAbility.generated.h"

class UWK_PlayerUIComponent;
class UWK_PlayerTargetLockComponent;
class AWK_PlayerController;
class AWK_PlayerCharacter;
/**
 * 
 */
UCLASS()
class WUKONG_API UWK_PlayerGameplayAbility : public UWK_GameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	AWK_PlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	UWK_PlayerComboComponent* GetPlayerComboComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	AWK_PlayerController* GetPlayerControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	UWK_PlayerTargetLockComponent* GetPlayerTargetLockComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	UWK_PlayerUIComponent* GetPlayerUIComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Player|Ability")
	FGameplayEffectSpecHandle MakePlayerGameplayEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, float BaseDamage, FGameplayTag AttackType, int32 ComboCount, int32 level, float MaxHitCount);
private:
	TWeakObjectPtr<AWK_PlayerCharacter> CachedPlayerCharacter;
	TWeakObjectPtr<AWK_PlayerController> CachedPlayerController;
};
