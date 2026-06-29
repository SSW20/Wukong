// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Ability/WK_PlayerGameplayAbility.h"

#include "WK_GameplayTags.h"
#include "AbilitySystem/WK_AbilitySystemComponent.h"
#include "Character/WK_PlayerCharacter.h"
#include "Controller/WK_PlayerController.h"

AWK_PlayerCharacter* UWK_PlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<AWK_PlayerCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedPlayerCharacter.Get();
}

UWK_PlayerComboComponent* UWK_PlayerGameplayAbility::GetPlayerComboComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerComboComponent();
}

AWK_PlayerController* UWK_PlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<AWK_PlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedPlayerController.Get();
}

UWK_PlayerTargetLockComponent* UWK_PlayerGameplayAbility::GetPlayerTargetLockComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerTargetLockComponent();
}

UWK_PlayerUIComponent* UWK_PlayerGameplayAbility::GetPlayerUIComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerUIComponent();
}

FGameplayEffectSpecHandle UWK_PlayerGameplayAbility::MakePlayerGameplayEffectSpecHandle(
	TSubclassOf<UGameplayEffect> Effect, float BaseDamage, FGameplayTag AttackType,int32 ComboCount, int32 level, float MaxHitCount)
{
	if (UWK_AbilitySystemComponent* PlayerASC = GetWKAbilitySystemComponent())
	{
		FGameplayEffectContextHandle Handle = PlayerASC->MakeEffectContext();
		Handle.SetAbility(this);
		Handle.AddSourceObject(GetPlayerCharacterFromActorInfo());
		Handle.AddInstigator(GetAvatarActorFromActorInfo(),GetAvatarActorFromActorInfo());

		FGameplayEffectSpecHandle SpecHandle = PlayerASC->MakeOutgoingSpec(Effect, level, Handle);
		
		// 나중에 콤보 카운트 넣으면 됨
		SpecHandle.Data->SetSetByCallerMagnitude(AttackType, ComboCount);
		SpecHandle.Data->SetSetByCallerMagnitude(WKGameplayTags::SetByCaller_Shared_BaseDamage, BaseDamage);
		SpecHandle.Data->SetSetByCallerMagnitude(WKGameplayTags::SetByCaller_Player_HitCount, MaxHitCount);
		return SpecHandle;
	}
	return nullptr;
}
