// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/UI/WK_PlayerUIComponent.h"

#include "AbilitySystemComponent.h"
#include "Actions/WK_AsyncTaskCooldownChanged.h"


// void UWK_PlayerUIComponent::StartCooldownListener(UAbilitySystemComponent* InASC, FGameplayTagContainer InCooldownTags)
// {
// 	if (!IsValid(InASC) || InCooldownTags.Num() == 0)
// 	{
// 		return;
// 	}
// 	
// 	// AsyncTask 1개 생성 (여기서 4개 태그 다 감시)
// 	CooldownTask = UWK_AsyncTaskCooldownChanged::Listen(InASC, InCooldownTags);
// 	if (!CooldownTask) return;
//
// 	OnCooldownTaskReady.Broadcast(CooldownTask);
// }

