// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_ExecuteOnTick.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickDelegate, float, DeltaTime);
/**
 * 
 */
UCLASS()
// ReSharper disable once CppUE4CodingStandardUClassNamingViolationError
class WUKONG_API UAbilityTask_ExecuteOnTick : public UAbilityTask
{
	GENERATED_BODY()
public:
	UAbilityTask_ExecuteOnTick();

	UFUNCTION(BlueprintCallable, Category = "AbilityTasks",
		meta = (HidePin = "OwningAbility",DefaultToSelf = "OwningAbility",BlueprintInternalUseOnly = "true"))
	static UAbilityTask_ExecuteOnTick* ExecuteOnTick(UGameplayAbility* OwningAbility);
	
	virtual void TickTask(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskTickDelegate OnAbilityTaskTick;
};
