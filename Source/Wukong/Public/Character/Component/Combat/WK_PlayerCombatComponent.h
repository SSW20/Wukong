// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WK_PawnCombatComponent.h"
#include "Components/ActorComponent.h"
#include "Types/WK_StructTypes.h"
#include "WK_PlayerCombatComponent.generated.h"


class UNiagaraSystem;
class UCapsuleComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWK_PlayerCombatComponent : public UWK_PawnCombatComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWK_PlayerCombatComponent();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void WeaponHitBegin(AActor* TargetActor) override;
	virtual void WeaponHitEnd(AActor* TargetActor) override;
	
	virtual void ToggleCollision(bool bShouldEnable,bool bFoot, FName LeftCollisionStart = FName("None"), FName RightCollisionStart = FName("None")) override;

	void UpdateCollision(UCapsuleComponent* Capsule, USkeletalMeshComponent* Mesh);
	void RestoreCapsuleCollision(UCapsuleComponent* Capsule);
private:
	// 오공 , 아크샤의 왕만 해당
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName WeaponStartSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	FName WeaponEndSocketName;


	
	UPROPERTY()
	FWeaponCollisionCachedData CachedWeaponCollisionData;
};
