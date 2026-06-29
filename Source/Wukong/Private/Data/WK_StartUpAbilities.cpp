// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WK_StartUpAbilities.h"
#include "AbilitySystem/Ability/WK_GameplayAbility.h"
#include "AbilitySystem/WK_AbilitySystemComponent.h"

void UWK_StartUpAbilities::GrantAbilityToActorASC(UWK_AbilitySystemComponent* WKAbilitySystemComponent, float Level)
{
	// Init Effect 적용 시키기 전에 overlay widget을 생성해야됨
	// 원래는 이런 순서
	// 	PlayerCharacter 생성
	// AbilitySystemComponent 생성
	// AttributeSet 생성
	// 초기 GameplayEffect 적용 → CurrentHealth(0→50) 변함
	// PlayerUIComponent 생성됨
	// HUD 생성
	// WBP_PlayerOverlay 생성
	// Widget 내부 Bind Event 실행 (이때부터 이벤트 듣기 시작)
	
	GrantAbilities(OnGivenAbilities, WKAbilitySystemComponent, Level);
	if (!OnGivenEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& OnGameplayEffectClass : OnGivenEffects)
		{
			UGameplayEffect* Effect = OnGameplayEffectClass->GetDefaultObject<UGameplayEffect>();
			if (Effect)
			{
				WKAbilitySystemComponent->ApplyGameplayEffectToSelf(Effect, Level, WKAbilitySystemComponent->MakeEffectContext());
			}

		}
	}
}

void UWK_StartUpAbilities::GrantAbilities(const TArray<TSubclassOf<UWK_GameplayAbility>>& Abilities,
                                          UWK_AbilitySystemComponent* WKAbilitySystemComponent, float Level)
{
	if (Abilities.Num() == 0) return;
	if (WKAbilitySystemComponent == nullptr) return;
	for (const TSubclassOf<UWK_GameplayAbility>& Ability : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.Level = Level;
		AbilitySpec.SourceObject = WKAbilitySystemComponent->GetAvatarActor();
		WKAbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}
