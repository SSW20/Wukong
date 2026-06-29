// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "WK_StartUpAbilities.generated.h"

class UWK_AbilitySystemComponent;
class UWK_GameplayAbility;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FPlayerAbilityData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Ability")
	TSubclassOf<UWK_GameplayAbility> Ability = nullptr;

	UPROPERTY(EditAnywhere, Category="Ability")
	FGameplayTag InputTag;
	
};

UCLASS()
class WUKONG_API UWK_StartUpAbilities : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void GrantAbilityToActorASC(UWK_AbilitySystemComponent* WKAbilitySystemComponent, float Level);
protected:
	// 피격, 강피격
	UPROPERTY(EditDefaultsOnly, Category="StartUp")
	TArray<TSubclassOf<UWK_GameplayAbility>> OnGivenAbilities;

	// Attribute 초기화
	UPROPERTY(EditDefaultsOnly, Category="StartUp")
	TArray<TSubclassOf<UGameplayEffect>> OnGivenEffects;

	void GrantAbilities(const TArray<TSubclassOf<UWK_GameplayAbility>>& Abilities, UWK_AbilitySystemComponent* WKAbilitySystemComponent, float Level);
};


