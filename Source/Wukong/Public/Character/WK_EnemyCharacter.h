// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "WK_BaseCharacter.h"
#include "WK_EnemyCharacter.generated.h"

class UNiagaraComponent;
class UWK_EnemyAttackPool;
class UWK_EnemyStartUpAbilities;
class UWidgetComponent;
class UWK_EnemyCombatComponent;

UCLASS()
class WUKONG_API AWK_EnemyCharacter : public AWK_BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWK_EnemyCharacter();
	
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UFUNCTION()	
	virtual void OnComponentBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// PawnCombatInterface
	virtual UWK_PawnCombatComponent* GetPawnCombatComponent() override;
	UWK_EnemyCombatComponent* GetEnemyCombatComponent() const {return EnemyCombatComponent;}
	
	// PawnUIInterface
	virtual UWK_PawnUIComponent* GetPawnUIComponent() const override;
	virtual UWK_EnemyUIComponent* GetEnemyUIComponent() const override {return EnemyUIComponent;}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnemyMaxWalkSpeed = 30.f;

	UFUNCTION(BlueprintCallable)
	UCapsuleComponent* GetEnemyLeftWeaponCollision() {return LeftHandCollisionBox;}

	UFUNCTION(BlueprintCallable)
	UCapsuleComponent* GetEnemyRightWeaponCollision() {return RightHandCollisionBox;}

	UFUNCTION(BlueprintCallable)
	UCapsuleComponent* GetEnemyLeftFootWeaponCollision() {return LeftFootCollisionBox;}

	UFUNCTION(BlueprintCallable)
	UCapsuleComponent* GetEnemyRightFootWeaponCollision() {return RightFootCollisionBox;}
	
	UFUNCTION(BlueprintCallable)
	UWK_EnemyAttackPool* GetEnemyAttackPoolData() const {return EnemyAttackPoolData;}

	UFUNCTION(BlueprintCallable)
	FName GetEnemyName() const {return EnemyName;}

	UFUNCTION(BlueprintCallable)
	float GetAcceptRadius() {return AcceptRadius;}

	UFUNCTION(BlueprintCallable)
	TArray<UNiagaraComponent*> GetEnemyNiagaraComponents() {return EnemyNiagaraComponents;}

	UFUNCTION(BlueprintCallable)
	void AddEnemyNiagaraComponents(UNiagaraComponent* NiagaraComponent) {EnemyNiagaraComponents.AddUnique(NiagaraComponent);}

	UFUNCTION(BlueprintCallable)
	void ClearSound();
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	FName EnemyName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UWK_EnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UWK_EnemyUIComponent* EnemyUIComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* EnemyWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	float AcceptRadius = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound",meta = (AllowPrivateAccess = "true"))
	USoundBase* OST;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* LeftWeaponSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* RightWeaponSound;
	
	UPROPERTY()
	UAudioComponent* OSTAudioComp;

	UPROPERTY()
	UAudioComponent* LeftWeaponAudioComp;

	UPROPERTY()
	UAudioComponent* RightWeaponAudioComp;
#pragma endregion Component

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* LeftHandCollisionBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* RightHandCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* LeftFootCollisionBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* RightFootCollisionBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName LeftHandAttachSocketName;   
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName RightHandAttachSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName LeftFootAttachSocketName;   
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName RightFootAttachSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	TArray<UNiagaraComponent*> EnemyNiagaraComponents;
	
	// 오공 , 아크샤의 왕만 해당
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName LeftStartSocket;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName LeftEndSocket;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName RightStartSocket;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName RightEndSocket;
	
	// UFUNCTION()
	// virtual void OnHandCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	// 	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//

	UPROPERTY(EditDefaultsOnly, Category="StartUp")
	TSoftObjectPtr<UWK_EnemyStartUpAbilities> EnemyStartAbilityData;

	UPROPERTY(EditDefaultsOnly, Category="Attack")
	UWK_EnemyAttackPool* EnemyAttackPoolData;

	
#if WITH_EDITOR
	// 프로퍼티 수정 시 호출되는 함수
	//~ Begin UObject Interface.
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject Interface
#endif
	

};
