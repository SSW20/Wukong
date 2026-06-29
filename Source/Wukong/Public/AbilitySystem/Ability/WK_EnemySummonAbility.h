// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WK_EnemyGameplayAbility.h"
#include "WK_EnemySummonAbility.generated.h"

class AWK_AreaActorBase;
class AWK_ProjectileBase;
/**
 * 
 */
UCLASS()
class WUKONG_API UWK_EnemySummonAbility : public UWK_EnemyGameplayAbility
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FRotator& SpawnRotator, const FVector& SpawnLocation,
		AActor* HomingTarget,TSubclassOf<UGameplayEffect> DamageClass, float InDamage, bool bGround, bool bHoming);

	UFUNCTION(BlueprintCallable)
	void SpawnRing(const FRotator& SpawnRotator, const FVector& SpawnLocation, TSubclassOf<UGameplayEffect> DamageClass, float InDamage);
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AWK_ProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<AWK_AreaActorBase> RingClass;
	
	UPROPERTY(EditDefaultsOnly)
	int32 NumProjectiles = 5;

	UPROPERTY(EditDefaultsOnly)
	int32 HomingAccelarationMax = 3200.f;

	UPROPERTY(EditDefaultsOnly)
	int32 HomingAccelarationMin = 1600.f;
};
