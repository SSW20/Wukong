// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/WK_AreaActorBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "WK_BlueprintFunctionLibrary.h"
#include "WK_GameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/WK_PawnCombatInterface.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Wukong/Wukong.h"


// Sets default values
AWK_AreaActorBase::AWK_AreaActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetCollisionObjectType(ECC_Ring);
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AWK_AreaActorBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	CurrentRadius = 0.f;
	Sphere->SetSphereRadius(CurrentRadius + RingWidth, true);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereEndOverlap);
	
	ShockwaveNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ShockwaveNiagaraEffect,
		GetActorLocation(), GetActorRotation());
}

// Called every frame
void AWK_AreaActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentRadius += ExpandSpeed * DeltaTime;
	Sphere->SetSphereRadius(CurrentRadius + RingWidth * 0.5f, true);

	float ShockwaveEffectRadius = CurrentRadius + RingWidth * 0.5f; 
	float ScaleEffect = ShockwaveEffectRadius / 208;

	ShockwaveNiagaraComponent->SetWorldScale3D(FVector(ScaleEffect, ScaleEffect, 1.0f));
	DebugDraw();
}

void AWK_AreaActorBase::Destroyed()
{
	Super::Destroyed();
	OverlappingTargets.Empty();
}

void AWK_AreaActorBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsTargetValid(OtherActor)) return;
	if (CanHitTarget(OtherActor))
	{
		ApplyDamage(OtherActor);
	}
}

void AWK_AreaActorBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

bool AWK_AreaActorBase::CanHitTarget(AActor* Target) const
{
	if (Target == nullptr) return false;

	if (UCharacterMovementComponent* MovementComp = Cast<ACharacter>(Target)->GetCharacterMovement())
	{
		bool bFalling = MovementComp->IsFalling();
		ACharacter* TargetCharacter = Cast<ACharacter>(Target);
		UCapsuleComponent* CapsuleComp = TargetCharacter->GetCapsuleComponent();
		if (!CapsuleComp) return false;
		const float TargetFootZ = TargetCharacter->GetActorLocation().Z - CapsuleComp->GetScaledCapsuleHalfHeight();
		bool High = TargetFootZ > GetActorLocation().Z +  AcceptanceZ;

		return !(bFalling || High);
	}
	return false;
	
}

bool AWK_AreaActorBase::TargetInWidth(AActor* Target) const
{
	const FVector Center = GetActorLocation();
	const FVector TargetLoc = Target->GetActorLocation();

	const float Dist2D = FVector::Dist2D(Center, TargetLoc);
	const float HalfWidth = RingWidth * 0.5f;

	// 테두리 아니면 무시
	if (FMath::Abs(Dist2D - CurrentRadius) > HalfWidth)
	{
		return false;
	}
	return true;
}

bool AWK_AreaActorBase::IsTargetValid(AActor* Target) const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	APawn* TargetPawn = Cast<APawn>(Target);

	if (OwnerPawn == nullptr || Target == nullptr) return false;
	return UWK_BlueprintFunctionLibrary::IsTargetHostile(TargetPawn, OwnerPawn);
}

void AWK_AreaActorBase::DebugDraw() const
{
	if (!GetWorld()) return;

	const FVector Center = GetActorLocation();


	const FVector Up = FVector::UpVector;


	const FVector XAxis = FVector::ForwardVector;               
	const FVector YAxis = FVector::CrossProduct(Up, XAxis);     

	DrawDebugCircle(GetWorld(), Center, FMath::Max(0.f, CurrentRadius - RingWidth),
		64, FColor::Cyan, false, 0.f, 0, 2.f, XAxis, YAxis, false);

	DrawDebugCircle(GetWorld(), Center, CurrentRadius,
		64, FColor::Yellow, false, 0.f, 0, 2.f, XAxis, YAxis, false);
}

void AWK_AreaActorBase::ApplyDamage(AActor* OtherActor)
{
	if (!OtherActor->Implements<UWK_PawnCombatInterface>()) return;
	
	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	FGameplayEffectContextHandle ContextHandle = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner())->MakeEffectContext();
	ContextHandle.AddSourceObject(GetOwner()); // 또는 this
	ContextHandle.AddInstigator(GetOwner(),GetOwner());
	FGameplayEffectSpecHandle DamageSpec = OwnerASC->MakeOutgoingSpec(DamageEffectClass, 1.f, ContextHandle);
	if (!DamageSpec.IsValid()) return;
	
	DamageSpec.Data->SetSetByCallerMagnitude(WKGameplayTags::SetByCaller_Shared_BaseDamage, Damage);
	bDidHitPlayer = true;
	FGameplayEventData Data;

	if (UWK_BlueprintFunctionLibrary::ActorHasTag(OtherActor, WKGameplayTags::Player_Status_Parry))
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, WKGameplayTags::Event_Player_ParrySuccess , Data);
		return;
	}
	
	Data.Instigator = GetOwner();
	Data.Target = OtherActor;
	if (UWK_BlueprintFunctionLibrary::ActorHasTag(OtherActor, WKGameplayTags::Player_Status_Invincible))
	{
		if (UWK_BlueprintFunctionLibrary::ActorHasTag(OtherActor, WKGameplayTags::Player_Status_PerfectDodge))
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, WKGameplayTags::Event_Player_PerfectDodge , Data);
		}
		return;
	}
	UWK_BlueprintFunctionLibrary::NativeApplyEffectToTarget(OtherActor, DamageSpec);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, WKGameplayTags::Event_Shared_Hit_React_Shrink , Data);
}

