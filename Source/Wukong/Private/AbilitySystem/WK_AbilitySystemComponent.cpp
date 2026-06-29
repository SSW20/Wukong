// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WK_AbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WK_GameplayTags.h"
#include "Character/Component/Combat/Combo/WK_PlayerComboComponent.h"


// Called when the game starts
void UWK_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWK_AbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag InputTag)
{
	if (!InputTag.IsValid()) return;

	// 나중에 여기서 하지 말고 다른데서 할 것 
	if (InputTag.MatchesTag(WKGameplayTags::Player_Input_Trigger_Attack_Light))
	{
		if (UWK_PlayerComboComponent* ComboComponent = GetAvatarActor()->FindComponentByClass<UWK_PlayerComboComponent>())
		{
			ComboComponent->RegisterAttackInput(InputTag);
		}
		return;
	}

	if (InputTag.MatchesTag(WKGameplayTags::Player_Input_Trigger_Dodge))
	{
		if (UWK_PlayerComboComponent* ComboComponent = GetAvatarActor()->FindComponentByClass<UWK_PlayerComboComponent>())
		{
			ComboComponent->RegisterDodgeInput(InputTag);
		}
		return;
	}
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			if (InputTag.MatchesTag(WKGameplayTags::Player_Input_Toggle) && AbilitySpec.IsActive())
			{
				CancelAbility(AbilitySpec.Ability);
			}
			
			else
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UWK_AbilitySystemComponent::OnAbilityInputReleased(FGameplayTag InputTag)
{
	if (!InputTag.IsValid() || !InputTag.MatchesTag(WKGameplayTags::Player_Input_Held)) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

bool UWK_AbilitySystemComponent::TryActivateAbilityByTag(const FGameplayTag& Tag)
{
	if (!Tag.IsValid()) return false;

	TArray<FGameplayAbilitySpec*> AbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag.GetSingleTagContainer(), AbilitySpecs);

	for (FGameplayAbilitySpec* AbilitySpec : AbilitySpecs)
	{
		return TryActivateAbility(AbilitySpec->Handle);
	}
	return false;
}



