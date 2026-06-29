// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/WK_EnemySummonAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/WK_AreaActorBase.h"
#include "Actor/WK_ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/WK_PawnCombatInterface.h"

void UWK_EnemySummonAbility::SpawnProjectile(const FRotator& SpawnRotator, const FVector& SpawnLocation,
AActor* HomingTarget,  TSubclassOf<UGameplayEffect> DamageClass, float InDamage, bool bGround, bool bHoming) 
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(SpawnRotator.Quaternion());
	
	AWK_ProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AWK_ProjectileBase>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);
	Projectile->InitDamage(InDamage, DamageClass);
	Projectile->SetHomingTarget(HomingTarget);
	Projectile->SetGround(bGround);
	Projectile->SetHoming(bHoming);
	Projectile->FinishSpawning(SpawnTransform);
}

void UWK_EnemySummonAbility::SpawnRing(const FRotator& SpawnRotator, const FVector& SpawnLocation, TSubclassOf<UGameplayEffect> DamageClass, float InDamage) 
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(SpawnRotator.Quaternion());

	AWK_AreaActorBase* RingActor = GetWorld()->SpawnActorDeferred<AWK_AreaActorBase>(
		RingClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (!IsValid(RingActor)) return;
	RingActor->InitDamage(InDamage, DamageClass);

	UWK_AbilitySystemComponent* ASC = GetWKAbilitySystemComponent();
	RingActor->FinishSpawning(SpawnTransform);
	
}

