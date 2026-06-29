// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "WK_AttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class IWK_PawnCombatInterface;
class IWK_PawnUIInterface;

UCLASS()
class WUKONG_API UWK_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UWK_AttributeSet();
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData CurrentHealth;	
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category="Attribute")
	FGameplayAttributeData CurrentMana;	
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,CurrentMana)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,MaxMana)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,CurrentStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,MaxStamina)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData CurrentGauge;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,CurrentGauge)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxGauge;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,MaxGauge)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,Damage)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData CurrentGourd;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,CurrentGourd)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	FGameplayAttributeData MaxGourd;
	ATTRIBUTE_ACCESSORS(UWK_AttributeSet,MaxGourd)

private:
	TWeakInterfacePtr<IWK_PawnUIInterface> CachedPawnUIInterface;
	TWeakInterfacePtr<IWK_PawnCombatInterface> CachedPawnCombatInterface;
};
