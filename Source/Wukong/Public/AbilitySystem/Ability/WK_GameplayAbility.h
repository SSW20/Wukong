// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WK_GameplayAbility.generated.h"

class UWK_AbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WUKONG_API UWK_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	UWK_AbilitySystemComponent* GetWKAbilitySystemComponent() const;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnInputReleased();
	
public:
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bActivateAfterGiven = false;
};
