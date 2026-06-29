// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/WK_GameplayAbility.h"
#include "WK_EnemyGameplayAbility.generated.h"

class UWK_EnemyUIComponent;
class UWK_EnemyCombatComponent;
class AWK_EnemyController;
class AWK_EnemyCharacter;
/**
 * 
 */
UCLASS()
class WUKONG_API UWK_EnemyGameplayAbility : public UWK_GameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	AWK_EnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure)
	UWK_EnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure)
	UWK_EnemyUIComponent* GetEnemyUIComponentFromActorInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> EnemyAnimationMontages;

	UFUNCTION(BlueprintPure)
	FGameplayEffectSpecHandle MakeEnemyEffectSpecHandle(TSubclassOf<UGameplayEffect> InEffectClass, float InEnemyDamage);
private:
	TWeakObjectPtr<AWK_EnemyCharacter> CachedWarriorEnemyCharacter;

	
};
