// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/Combat/WK_EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WK_GameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/WK_EnemyCharacter.h"
#include "Components/CapsuleComponent.h"


// Sets default values for this component's properties
UWK_EnemyCombatComponent::UWK_EnemyCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UWK_EnemyCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	AWK_EnemyCharacter* Enemy = Cast<AWK_EnemyCharacter>(GetOwner());
	if (!Enemy) return;

	UCapsuleComponent* LeftCapsule = Enemy->GetEnemyLeftWeaponCollision();
	UCapsuleComponent* RightCapsule = Enemy->GetEnemyRightWeaponCollision();
	
	LeftCachedWeaponCollisionData.Radius = LeftCapsule->GetUnscaledCapsuleRadius();
	LeftCachedWeaponCollisionData.HalfHeight = LeftCapsule->GetUnscaledCapsuleHalfHeight();
	LeftCachedWeaponCollisionData.RelLoc = LeftCapsule->GetRelativeLocation();
	LeftCachedWeaponCollisionData.RelRot = LeftCapsule->GetRelativeRotation();

	RightCachedWeaponCollisionData.Radius = RightCapsule->GetUnscaledCapsuleRadius();
	RightCachedWeaponCollisionData.HalfHeight = RightCapsule->GetUnscaledCapsuleHalfHeight();
	RightCachedWeaponCollisionData.RelLoc = RightCapsule->GetRelativeLocation();
	RightCachedWeaponCollisionData.RelRot = RightCapsule->GetRelativeRotation();

	LeftCachedWeaponStartSocketName = LeftWeaponStartSocketName;
	RightCachedWeaponStartSocketName = RightWeaponStartSocketName;
	
}

void UWK_EnemyCombatComponent::UpdateCollision(UCapsuleComponent* Capsule, USkeletalMeshComponent* Mesh, bool bleft)
{
	FVector WeaponStartLocation;
	FVector WeaponEndLocation;
	if (bleft == true)
	{
		WeaponStartLocation = Mesh->GetSocketLocation(LeftWeaponStartSocketName);
		WeaponEndLocation = Mesh->GetSocketLocation(LeftWeaponEndSocketName);
	}
	else
	{
		WeaponStartLocation = Mesh->GetSocketLocation(RightWeaponStartSocketName);
		WeaponEndLocation = Mesh->GetSocketLocation(RightWeaponEndSocketName);
	}
	
	const FVector WeaponVector = WeaponStartLocation - WeaponEndLocation;
	float WeaponLength = WeaponVector.Size();

	const FVector WeaponVectorNormalized = WeaponVector.GetSafeNormal();
	const FVector WeaponCenterLocation = (WeaponStartLocation + WeaponEndLocation) / 2.f;

	const FQuat CapsuleRotation = FRotationMatrix::MakeFromZ(WeaponVectorNormalized).ToQuat();

	const float CapsuleRadius = Capsule->GetUnscaledCapsuleRadius();
	const float CapsuleHalfHeight = WeaponLength * 0.5f;

	Capsule->SetWorldLocation(WeaponCenterLocation);
	Capsule->SetWorldRotation(CapsuleRotation);
	Capsule->SetCapsuleHalfHeight(CapsuleHalfHeight);
}

void UWK_EnemyCombatComponent::RestoreCapsuleCollision(UCapsuleComponent* Capsule, bool bLeft)
{
	if (bLeft == true)
	{
		Capsule->SetRelativeLocation(LeftCachedWeaponCollisionData.RelLoc);
		Capsule->SetRelativeRotation(LeftCachedWeaponCollisionData.RelRot);
		Capsule->SetCapsuleSize(LeftCachedWeaponCollisionData.Radius, LeftCachedWeaponCollisionData.HalfHeight, true);
	}
	else
	{
		Capsule->SetRelativeLocation(RightCachedWeaponCollisionData.RelLoc);
		Capsule->SetRelativeRotation(RightCachedWeaponCollisionData.RelRot);
		Capsule->SetCapsuleSize(RightCachedWeaponCollisionData.Radius, RightCachedWeaponCollisionData.HalfHeight, true);
	}

	if (LeftCachedWeaponStartSocketName != LeftWeaponStartSocketName)
	{
		LeftWeaponStartSocketName = LeftCachedWeaponStartSocketName;
	}
	if (RightCachedWeaponStartSocketName != RightWeaponStartSocketName)
	{
		RightWeaponStartSocketName = RightCachedWeaponStartSocketName;
	}
	
}


// Called every frame
void UWK_EnemyCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bUpdateWeaponCollision) return;
	
	AWK_EnemyCharacter* Enemy = Cast<AWK_EnemyCharacter>(GetOwner());
	if (!Enemy) return;

	UCapsuleComponent* LeftCapsule = Enemy->GetEnemyLeftWeaponCollision();
	UCapsuleComponent* RightCapsule = Enemy->GetEnemyRightWeaponCollision();
	USkeletalMeshComponent* Mesh = Enemy->GetMesh();
	if (!Mesh || !LeftCapsule || !RightCapsule) return;
	
	UpdateCollision(LeftCapsule, Mesh, true);
	UpdateCollision(RightCapsule, Mesh, false);
}

void UWK_EnemyCombatComponent::WeaponHitBegin(AActor* TargetActor)
{
	if (OverlappedActors.Contains(TargetActor))
	{
		return;
	}

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.EventTag = WKGameplayTags::Event_Shared_Hit_Melee;
	Data.Target = TargetActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WKGameplayTags::Event_Shared_Hit_Melee , Data);
	
	OverlappedActors.AddUnique(TargetActor);
}

void UWK_EnemyCombatComponent::WeaponHitEnd(AActor* TargetActor)
{
	Super::WeaponHitEnd(TargetActor);
}

void UWK_EnemyCombatComponent::ToggleCollision(bool bShouldEnable, bool bFoot, FName LeftCollisionStart, FName RightCollisionStart)
{
	AWK_EnemyCharacter* Enemy = Cast<AWK_EnemyCharacter>(GetOwner());
	if (bShouldEnable)
	{
		if (Enemy)
		{
			if (bFoot)
			{
				Enemy->GetEnemyLeftFootWeaponCollision()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				Enemy->GetEnemyLeftFootWeaponCollision()->SetGenerateOverlapEvents(true);
				Enemy->GetEnemyLeftFootWeaponCollision()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

				Enemy->GetEnemyRightFootWeaponCollision()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				Enemy->GetEnemyRightFootWeaponCollision()->SetGenerateOverlapEvents(true);
				Enemy->GetEnemyRightFootWeaponCollision()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
			}
			else
			{
				Enemy->GetEnemyLeftWeaponCollision()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				Enemy->GetEnemyLeftWeaponCollision()->SetGenerateOverlapEvents(true);
				Enemy->GetEnemyLeftWeaponCollision()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

				Enemy->GetEnemyRightWeaponCollision()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
				Enemy->GetEnemyRightWeaponCollision()->SetGenerateOverlapEvents(true);
				Enemy->GetEnemyRightWeaponCollision()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
			}
			if (LeftCollisionStart != FName("None") && RightCollisionStart != FName("None"))
			{
				LeftWeaponStartSocketName = LeftCollisionStart;
				RightWeaponStartSocketName = RightCollisionStart;
			}
		}
	}
	else
	{
		if (bFoot)
		{
			Enemy->GetEnemyRightFootWeaponCollision()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Enemy->GetEnemyRightFootWeaponCollision()->SetGenerateOverlapEvents(false);
			Enemy->GetEnemyLeftFootWeaponCollision()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Enemy->GetEnemyLeftFootWeaponCollision()->SetGenerateOverlapEvents(false);
		}
		else
		{
			Enemy->GetEnemyLeftWeaponCollision()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Enemy->GetEnemyLeftWeaponCollision()->SetGenerateOverlapEvents(false);
			Enemy->GetEnemyRightWeaponCollision()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Enemy->GetEnemyRightWeaponCollision()->SetGenerateOverlapEvents(false);
		}
		
		RestoreCapsuleCollision(Enemy->GetEnemyLeftWeaponCollision(), true);
		RestoreCapsuleCollision(Enemy->GetEnemyRightWeaponCollision(), false);
		OverlappedActors.Empty();
	}
}

