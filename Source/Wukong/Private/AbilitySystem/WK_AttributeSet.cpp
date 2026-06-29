// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WK_AttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "WK_BlueprintFunctionLibrary.h"
#include "WK_GameplayTags.h"
#include "Character/Component/Combat/WK_PlayerCombatComponent.h"
#include "Character/Component/Combat/Combo/WK_PlayerComboComponent.h"
#include "Character/Component/UI/WK_PlayerUIComponent.h"
#include "Interface/WK_PawnCombatInterface.h"
#include "Interface/WK_PawnUIInterface.h"
#include "Wukong/WK_DebugHelper.h"

UWK_AttributeSet::UWK_AttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentMana(1.f);
	InitMaxMana(1.f);
	InitCurrentStamina(1.f);
	InitMaxStamina(1.f);
	InitCurrentGauge(1.f);
	InitMaxGauge(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
	InitDamage(1.f);
	InitCurrentGourd(1.f);
	InitMaxGourd(1.f);
}

void UWK_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (CachedPawnUIInterface == nullptr)
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IWK_PawnUIInterface>(Data.Target.GetAvatarActor());
	}
	if (CachedPawnCombatInterface == nullptr)
	{
		CachedPawnCombatInterface = TWeakInterfacePtr<IWK_PawnCombatInterface>(Data.Target.GetAvatarActor());
	}

	UWK_PawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	UWK_PlayerUIComponent* PlayerUIComponent = CachedPawnUIInterface->GetPlayerUIComponent();
	UWK_PlayerComboComponent* PlayerComboComponent = CachedPawnCombatInterface->GetPlayerComboComponent();

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
		if (PawnUIComponent)
		{
			PawnUIComponent->OnHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentManaAttribute())
	{
		SetCurrentStamina(FMath::Clamp(GetCurrentMana(), 0.f, GetMaxMana()));
		if (PlayerUIComponent)
		{
			PlayerUIComponent->OnManaChanged.Broadcast(GetCurrentMana() / GetMaxMana());
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		SetCurrentStamina(FMath::Clamp(GetCurrentStamina(), 0.f, GetMaxStamina()));
		if (PlayerUIComponent)
		{
			PlayerUIComponent->OnStaminaChanged.Broadcast(GetCurrentStamina() / GetMaxStamina());
		}
		if (GetCurrentStamina() == 0)
		{
			UWK_BlueprintFunctionLibrary::AddGameplayTagToActor(GetOwningActor(), WKGameplayTags::Player_Status_NoStamina);
		}
		else
		{
			UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(GetOwningActor(), WKGameplayTags::Player_Status_NoStamina);
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentGaugeAttribute())
	{
		SetCurrentGauge(FMath::Clamp(GetCurrentGauge(), 0.f, GetMaxGauge()));
		if (GetCurrentGauge() == GetMaxGauge())
		{
			int32 ChargedCombo = PlayerComboComponent->GetCurrentChargedAttackComboIndex();
			if (ChargedCombo  <  PlayerComboComponent->ChargedAttackMontagesCount)
			{
				// 컴뱃 인터페이스 가져와서 current Gauge Point 가져온다음에 처리하기
				SetCurrentGauge(0.f);
				if (PlayerComboComponent)
				{
					PlayerComboComponent->SetCurrentChargedAttackComboIndex(ChargedCombo + 1);
				}
				if (PlayerUIComponent)
				{
					PlayerUIComponent->OnGaugePointChanged.Broadcast(ChargedCombo + 1);
					PlayerComboComponent->OnWeaponGaugeMax();
				}
			}
		}
		if (PlayerUIComponent)
		{
			PlayerUIComponent->OnGaugeChanged.Broadcast(GetCurrentGauge() / GetMaxGauge());
		}
	}

	// 호리병 처리
	if (Data.EvaluatedData.Attribute == GetCurrentGourdAttribute())
	{
		SetCurrentGourd(FMath::Clamp(GetCurrentGourd(), 0.f, GetMaxGourd()));
		if (PlayerUIComponent)
		{
			PlayerUIComponent->OnHealthPotionChanged.Broadcast(GetCurrentGourd() / GetMaxGourd());
		}
	}

	// 데미지 처리
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float IncomingDamage = GetDamage();
		SetDamage(0.f);
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth() - IncomingDamage, 0.f, GetMaxHealth()));
		if (PawnUIComponent)
		{
			PawnUIComponent->OnHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
		}

		if (GetCurrentHealth() <= 0.f)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Data.Target.GetAvatarActor(), WKGameplayTags::Shared_Status_Death, FGameplayEventData());
		}
	}
}
