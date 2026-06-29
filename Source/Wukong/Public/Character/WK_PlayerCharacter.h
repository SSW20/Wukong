// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WK_BaseCharacter.h"
#include "Interface/WK_PawnCombatInterface.h"
#include "Interface/WK_PawnUIInterface.h"
#include "WK_PlayerCharacter.generated.h"

class UWK_PlayerCombatComponent;
class UWK_PlayerComboComponent;
class UWK_PlayerUIComponent;
class UWK_PlayerTargetLockComponent;
struct FGameplayTag;
class UWK_PlayerStartUpAbilities;
class UWK_InputDataConfig;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class WUKONG_API AWK_PlayerCharacter : public AWK_BaseCharacter 
{
	GENERATED_BODY()

public:
	AWK_PlayerCharacter();
	UPROPERTY()
	float BufferedInputYaw = 0.0f;
protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()	
	virtual void OnComponentBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);

public:
	UWK_PlayerCombatComponent* GetPlayerCombatComponent() const {return PlayerCombatComponent;}
	UWK_PlayerUIComponent* GetPlayerUIComponent() const {return PlayerUIComponent;}

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// PawnCombatInterface
	virtual UWK_PawnCombatComponent* GetPawnCombatComponent() override;
	virtual UWK_PlayerComboComponent* GetPlayerComboComponent() override {return PlayerComboComponent; }
	virtual UWK_PlayerTargetLockComponent* GetPlayerTargetLockComponent()  override {return PlayerTargetLockComponent; }

	// PawnUIInterface
	virtual UWK_PawnUIComponent* GetPawnUIComponent() const override;
	
	
	void SetFollowPelvis(bool bFollow) {bFollowPelvis = bFollow; }
	UFUNCTION(BlueprintCallable)
	void BP_StopSprint();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AActor* GetTargetActor() const;

	UCapsuleComponent* GetWeaponCollisionBox() {return WeaponCollisionBox;}

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Homing", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> FootSceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UWK_PlayerComboComponent* PlayerComboComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWK_PlayerTargetLockComponent* PlayerTargetLockComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UWK_PlayerUIComponent* PlayerUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UWK_PlayerCombatComponent* PlayerCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* WeaponCollisionBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName WeaponAttachSocketName;   


#pragma endregion Components
	
#pragma region EnhancedInput
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="EnhancedInput", meta=(AllowPrivateAccess="true"))
	UWK_InputDataConfig* InputDataConfig;
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	
	void Input_Sprint_Start();
	void Input_Sprint_Stop();

	void Input_Walk_Start();
	void Input_Walk_Stop();

	void OnInputPressed(FGameplayTag InputTag);
	void OnInputReleased(FGameplayTag InputTag);
	
#pragma endregion EnhancedInput

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(AllowPrivateAccess = true))
	float DefaultSpeed = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(AllowPrivateAccess = true))
	float RunSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta =(AllowPrivateAccess = true))
	float WalkSpeed = 50.f;

	// TObjectPtr이나 * 의 강한참조를 쓰게 되면 Python에서의 Wrapping과정에서 Crash남
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class UWK_PlayerStartUpAbilities> PlayerStartAbilityData;

	FRotator InputRotation = FRotator::ZeroRotator;


	UPROPERTY()
	bool bFollowPelvis = false;

#if WITH_EDITOR
	// 프로퍼티 수정 시 호출되는 함수
	//~ Begin UObject Interface.
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject Interface
#endif
};

