// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WK_AbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWK_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void OnAbilityInputPressed(const FGameplayTag InputTag);
	void OnAbilityInputReleased(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable)
	bool TryActivateAbilityByTag(const FGameplayTag& Tag);
};
