// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/WK_PawnCombatInterface.h"
#include "Interface/WK_PawnUIInterface.h"
#include "WK_BaseCharacter.generated.h"

class UMotionWarpingComponent;
class UWK_AttributeSet;
class UWK_AbilitySystemComponent;

UCLASS()
class WUKONG_API AWK_BaseCharacter : public ACharacter,  public IWK_PawnCombatInterface, public IWK_PawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWK_BaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UWK_AbilitySystemComponent* WKAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	UWK_AttributeSet* WKAttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MotionWarp")
	UMotionWarpingComponent* MotionWarpingComponent;

	UFUNCTION(BlueprintCallable)
	void SetAnimRootMotionScaleInBP(float NewScale);
	
public:
	FORCEINLINE UWK_AbilitySystemComponent* GetWKAbilitySystemComponent() const {return WKAbilitySystemComponent;}
	FORCEINLINE UWK_AttributeSet* GetWKAttributeSet() const {return WKAttributeSet;}

	virtual UWK_PawnUIComponent* GetPawnUIComponent() const override;
	virtual UWK_PawnCombatComponent* GetPawnCombatComponent() override;

	UMotionWarpingComponent* GetMotionWarpingComponent() const {return MotionWarpingComponent;}
};
