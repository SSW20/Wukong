// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/AbilityTask_ExecuteOnTick.h"

UAbilityTask_ExecuteOnTick::UAbilityTask_ExecuteOnTick()
{
	bTickingTask = true;
}

UAbilityTask_ExecuteOnTick* UAbilityTask_ExecuteOnTick::ExecuteOnTick(UGameplayAbility* OwningAbility)
{
	UAbilityTask_ExecuteOnTick* TickTask = NewAbilityTask<UAbilityTask_ExecuteOnTick>(OwningAbility);
	return TickTask;
}

void UAbilityTask_ExecuteOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTaskTick.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}


