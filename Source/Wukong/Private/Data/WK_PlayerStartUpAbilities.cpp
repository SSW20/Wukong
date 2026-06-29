// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WK_PlayerStartUpAbilities.h"
#include "AbilitySystem/Ability/WK_GameplayAbility.h"
#include "AbilitySystem/WK_AbilitySystemComponent.h"

void UWK_PlayerStartUpAbilities::GrantAbilityToActorASC(UWK_AbilitySystemComponent* WKAbilitySystemComponent,
                                                        float Level)
{
	Super::GrantAbilityToActorASC(WKAbilitySystemComponent, Level);

	for (FPlayerAbilityData& PlayerAbility : PlayerAttackAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(PlayerAbility.Ability);
		AbilitySpec.SourceObject = WKAbilitySystemComponent->GetAvatarActor();
		AbilitySpec.Level = Level;
		AbilitySpec.DynamicAbilityTags.AddTag(PlayerAbility.InputTag);
		WKAbilitySystemComponent->GiveAbility(AbilitySpec);
	}

	for (FPlayerAbilityData& PlayerAbility : PlayerUtilAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(PlayerAbility.Ability);
		AbilitySpec.SourceObject = WKAbilitySystemComponent->GetAvatarActor();
		AbilitySpec.Level = Level;
		AbilitySpec.DynamicAbilityTags.AddTag(PlayerAbility.InputTag);
		WKAbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}
