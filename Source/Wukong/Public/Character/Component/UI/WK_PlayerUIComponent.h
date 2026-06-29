// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WK_PawnUIComponent.h"
#include "Actions/WK_AsyncTaskCooldownChanged.h"
#include "WK_PlayerUIComponent.generated.h"

class UAbilitySystemComponent;
class WK_AsyncTaskCooldownChanged;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPointChanged, int32, FPointChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCoolDownStarted, FGameplayTag, CoolDownTag, float, TotalTime, float, RemainTime);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWK_PlayerUIComponent : public UWK_PawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FPercentChanged OnManaChanged;

	UPROPERTY(BlueprintAssignable)
	FPercentChanged OnStaminaChanged;

	UPROPERTY(BlueprintAssignable)
	FPercentChanged OnGaugeChanged;

	UPROPERTY(BlueprintAssignable)
	FPercentChanged OnHealthPotionChanged;
	
	UPROPERTY(BlueprintAssignable)
	FPointChanged OnGaugePointChanged;

	// UFUNCTION(BlueprintCallable)
	// void StartCooldownListener(UAbilitySystemComponent* InASC, FGameplayTagContainer InCooldownTags);

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FCoolDownStarted OnCooldownStarted;
private:
	// UPROPERTY()
	// TObjectPtr<UWK_AsyncTaskCooldownChanged> CooldownTask;
};