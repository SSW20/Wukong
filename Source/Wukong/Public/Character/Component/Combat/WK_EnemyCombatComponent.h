// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WK_PawnCombatComponent.h"
#include "Types/WK_StructTypes.h"
#include "WK_EnemyCombatComponent.generated.h"


class UCapsuleComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWK_EnemyCombatComponent : public UWK_PawnCombatComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWK_EnemyCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void UpdateCollision(UCapsuleComponent* Capsule, USkeletalMeshComponent* Mesh, bool bLeft);
	void RestoreCapsuleCollision(UCapsuleComponent* Capsule, bool bLeft);
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void WeaponHitBegin(AActor* TargetActor) override;
	virtual void WeaponHitEnd(AActor* TargetActor) override;
	
	virtual void ToggleCollision(bool bShouldEnable,bool bFoot, FName LeftCollisionStart = FName("None"), FName RightCollisionStart = FName("None")) override;

	
private:
	// 오공 , 아크샤의 왕만 해당
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName LeftWeaponStartSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName LeftWeaponEndSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName RightWeaponStartSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName RightWeaponEndSocketName;

	UPROPERTY()
	FWeaponCollisionCachedData LeftCachedWeaponCollisionData;

	UPROPERTY()
	FWeaponCollisionCachedData RightCachedWeaponCollisionData;

	UPROPERTY()
	FName RightCachedWeaponStartSocketName;

	UPROPERTY()
	FName LeftCachedWeaponStartSocketName;
};
