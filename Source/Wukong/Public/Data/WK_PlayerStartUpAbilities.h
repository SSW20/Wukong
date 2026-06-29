// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WK_StartUpAbilities.h"
#include "WK_PlayerStartUpAbilities.generated.h"

/**
 * 
 */



UCLASS()
class WUKONG_API UWK_PlayerStartUpAbilities : public UWK_StartUpAbilities
{
	GENERATED_BODY()
public:
	virtual void GrantAbilityToActorASC(UWK_AbilitySystemComponent* WKAbilitySystemComponent, float Level) override;

protected:
	// 약공격 , 강공격, 술법(분신술 , 변신 , 철벽 , 정지술) 중 1개   ==> 무조건 Input Tag 포함
	UPROPERTY(EditDefaultsOnly, Category="StartUp")
	TArray<FPlayerAbilityData> PlayerAttackAbilities;

	// 회피 , 극한 회피 , 호리병으로 회복   ==> 무조건 Input Tag 포함
	UPROPERTY(EditDefaultsOnly, Category="StartUp")
	TArray<FPlayerAbilityData> PlayerUtilAbilities;

};
