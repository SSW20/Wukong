// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/WK_EnemyGameplayAbility.h"
#include "WK_GameplayTags.h"
#include "AbilitySystem/WK_AbilitySystemComponent.h"
#include "Character/WK_EnemyCharacter.h"

AWK_EnemyCharacter* UWK_EnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedWarriorEnemyCharacter.IsValid())
	{
		CachedWarriorEnemyCharacter = Cast<AWK_EnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedWarriorEnemyCharacter.Get();
}

UWK_EnemyCombatComponent* UWK_EnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

UWK_EnemyUIComponent* UWK_EnemyGameplayAbility::GetEnemyUIComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyUIComponent();
}


FGameplayEffectSpecHandle UWK_EnemyGameplayAbility::MakeEnemyEffectSpecHandle(
	TSubclassOf<UGameplayEffect> InEffectClass, float InEnemyDamage)
{
	check(InEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetWKAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle SpecHandle = GetWKAbilitySystemComponent()->MakeOutgoingSpec(
		InEffectClass, GetAbilityLevel(), ContextHandle);
	
	SpecHandle.Data.Get()->SetSetByCallerMagnitude(WKGameplayTags::SetByCaller_Shared_BaseDamage,
												   InEnemyDamage);

	return SpecHandle;
}




