// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/WK_GameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WK_AbilitySystemComponent.h"

UWK_AbilitySystemComponent* UWK_GameplayAbility::GetWKAbilitySystemComponent() const
{
	return Cast<UWK_AbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}



void UWK_GameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	BP_OnInputReleased();
}

void UWK_GameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (bActivateAfterGiven)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}
