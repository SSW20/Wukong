// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WK_EnemyStartUpAbilities.h"

#include "AbilitySystem/WK_AbilitySystemComponent.h"

void UWK_EnemyStartUpAbilities::GrantAbilityToActorASC(UWK_AbilitySystemComponent* WKAbilitySystemComponent,
                                                       float Level)
{
	Super::GrantAbilityToActorASC(WKAbilitySystemComponent, Level);
	GrantAbilities(EnemyStartUpAbilities,WKAbilitySystemComponent, Level);
}
