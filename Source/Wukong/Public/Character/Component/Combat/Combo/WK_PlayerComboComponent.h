// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Abilities/GameplayAbility.h"
#include "Character/Component/WK_PawnComponentBase.h"
#include "Components/ActorComponent.h"
#include "Types/WK_StructTypes.h"
#include "WK_PlayerComboComponent.generated.h"


class AWK_PlayerCharacter;
class AWK_BaseCharacter;
struct FGameplayTag;
class UWK_GameplayAbility;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWK_PlayerComboComponent : public UWK_PawnComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWK_PlayerComboComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TArray<TSubclassOf<UGameplayAbility>> LightComboAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TArray<FActorDodgeAbility> DodgeComboAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	int32 ChargedAttackMontagesCount = 3;

	UPROPERTY(EditDefaultsOnly)
	float InitialNiagaraSystemSize = 0.8f;

	UPROPERTY(EditDefaultsOnly)
	float IncreaseNiagaraSystemSizeScale = 0.1f;
	
	bool bNextLightAttack = true;
	bool bNextDodge = false;
	bool bIsWindowOpen = true;
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RegisterAttackInput(const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RegisterDodgeInput(const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ResetLightCombo();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ResetDodgeCombo();

	TSubclassOf<UGameplayAbility> FindActorDodgeAbility(const EActorDirection& ActorDir);
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	inline FVector GetDodgeDirection() const { return CurrentDodgeDirection;};

	UFUNCTION(BlueprintCallable, Category = "Combat")
	inline int GetCurrentLightComboIndex() const { return CurrentLightComboIndex;};

	UFUNCTION(BlueprintCallable, Category = "Combat")
	inline int GetCurrentDodgeComboIndex() const { return CurrentDodgeComboIndex;};

	UFUNCTION(BlueprintCallable, Category = "Combat")
	inline int GetCurrentChargedAttackComboIndex() const { return CurrentChargedAttackComboIndex;};

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetCurrentChargedAttackComboIndex(int32 NewCount);

	
	// 게이지 모았을 때 나이아가라 이펙트
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnWeaponGaugeMax();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	USoundBase* GaugeMaxSound;

private:
	AWK_PlayerCharacter* Owner;

	FVector CurrentDodgeDirection = FVector::ZeroVector;

	int CurrentLightComboIndex = -1;
	int CurrentDodgeComboIndex = -1;
	int DodgeComboMontages = 3;
	int CurrentChargedAttackComboIndex = 0;

	
	
	UPROPERTY()
	UNiagaraComponent* WeaponEndNiagaraComponent;

	UPROPERTY()
	UNiagaraComponent* WeaponStartNiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	UNiagaraSystem* WeaponEndNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	UNiagaraSystem* WeaponStartNiagaraSystem;
};
