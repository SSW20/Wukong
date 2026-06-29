// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WK_BaseCharacter.h"
#include "WK_PlayerCloneCharacter.generated.h"

class UWK_PlayerCombatComponent;

UCLASS()
class WUKONG_API AWK_PlayerCloneCharacter : public AWK_BaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWK_PlayerCloneCharacter();

protected:
	// Called when the game starts or when spawned
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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UWK_PlayerCombatComponent* GetPlayerCombatComponent() const {return PlayerCombatComponent;}
	virtual UWK_PawnCombatComponent* GetPawnCombatComponent() override;
	UCapsuleComponent* GetWeaponCollisionBox() {return WeaponCollisionBox;}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UWK_PlayerCombatComponent* PlayerCombatComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* WeaponCollisionBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName WeaponAttachSocketName;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<class UWK_StartUpAbilities> PlayerCloneStartAbilityData;
};
