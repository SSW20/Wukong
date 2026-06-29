// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/Combat/WK_PlayerCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "WK_GameplayTags.h"
#include "Character/WK_PlayerCharacter.h"
#include "Character/WK_PlayerCloneCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Wukong/WK_DebugHelper.h"


// Sets default values for this component's properties
UWK_PlayerCombatComponent::UWK_PlayerCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}




// Called when the game starts
void UWK_PlayerCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	AWK_PlayerCharacter* Player = Cast<AWK_PlayerCharacter>(GetOwner());
	if (!Player) return;

	UCapsuleComponent* Capsule = Player->GetWeaponCollisionBox();

	CachedWeaponCollisionData.Radius = Capsule->GetUnscaledCapsuleRadius();
	CachedWeaponCollisionData.HalfHeight = Capsule->GetUnscaledCapsuleHalfHeight();
	CachedWeaponCollisionData.RelLoc = Capsule->GetRelativeLocation();
	CachedWeaponCollisionData.RelRot = Capsule->GetRelativeRotation();
}



// Called every frame
void UWK_PlayerCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bUpdateWeaponCollision) return;
	if (!WeaponEndSocketName.IsValid() || !WeaponStartSocketName.IsValid()) return;
	
	AWK_PlayerCharacter* Player = Cast<AWK_PlayerCharacter>(GetOwner());
	if (!Player) return;

	UCapsuleComponent* Capsule = Player->GetWeaponCollisionBox();
	USkeletalMeshComponent* Mesh = Player->GetMesh();
	if (!Mesh || !Capsule) return;
	
	UpdateCollision(Capsule, Mesh);
	
}

void UWK_PlayerCombatComponent::WeaponHitBegin(AActor* TargetActor)
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

void UWK_PlayerCombatComponent::WeaponHitEnd(AActor* TargetActor)
{

}

void UWK_PlayerCombatComponent::ToggleCollision(bool bShouldEnable, bool bFoot, FName LeftCollisionStart, FName RightCollisionStart)
{
	AWK_PlayerCharacter* Player = Cast<AWK_PlayerCharacter>(GetOwner());
	AWK_PlayerCloneCharacter* Clone = Cast<AWK_PlayerCloneCharacter>(GetOwner());

	if (bShouldEnable)
	{
		if (Player)
		{
			Player->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			Player->GetWeaponCollisionBox()->SetGenerateOverlapEvents(true);
			Player->GetWeaponCollisionBox()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		}
		else
		{
			Clone->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			Clone->GetWeaponCollisionBox()->SetGenerateOverlapEvents(true);
			Clone->GetWeaponCollisionBox()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		}
	}
	else
	{
		if (Player)
		{
			Player->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Player->GetWeaponCollisionBox()->SetGenerateOverlapEvents(false);
			OverlappedActors.Empty();
			
			bUpdateWeaponCollision = false;
			RestoreCapsuleCollision(Player->GetWeaponCollisionBox());
		}
		else
		{
			Clone->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Clone->GetWeaponCollisionBox()->SetGenerateOverlapEvents(false);
			OverlappedActors.Empty();
		}
		
	}
}

void UWK_PlayerCombatComponent::UpdateCollision(UCapsuleComponent* Capsule, USkeletalMeshComponent* Mesh)
{
	const FVector WeaponStartLocation = Mesh->GetSocketLocation(WeaponStartSocketName);
	const FVector WeaponEndLocation = Mesh->GetSocketLocation(WeaponEndSocketName);

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


	// DrawDebugCapsule(
	// GetWorld(),
	// WeaponCenterLocation,
	// CapsuleHalfHeight,
	// CapsuleRadius,
	// CapsuleRotation,
	// FColor::Red,
	// true,   // persistent
	// 0.f,     // duration (0이면 한 프레임)
	// 0,
	// 1.f);
}

void UWK_PlayerCombatComponent::RestoreCapsuleCollision(UCapsuleComponent* Capsule)
{
 	Capsule->SetRelativeLocation(CachedWeaponCollisionData.RelLoc);
	Capsule->SetRelativeRotation(CachedWeaponCollisionData.RelRot);
	Capsule->SetCapsuleSize(CachedWeaponCollisionData.Radius, CachedWeaponCollisionData.HalfHeight, true);
}