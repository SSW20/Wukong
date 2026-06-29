// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/WK_ProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "WK_BlueprintFunctionLibrary.h"
#include "WK_GameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/WK_PawnCombatInterface.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWK_ProjectileBase::AWK_ProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
}

bool AWK_ProjectileBase::IsValidOverlap(AActor* OtherActor)
{
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OtherPawn == nullptr || OwnerPawn == nullptr) return false;
	return UWK_BlueprintFunctionLibrary::IsTargetHostile(OwnerPawn,OtherPawn);
}


void AWK_ProjectileBase::TickHomingGround(float DeltaTime)
{
}

void AWK_ProjectileBase::TickHomingTarget(float DeltaTime)
{
}

void AWK_ProjectileBase::TickGround(float DeltaTime)
{
}

void AWK_ProjectileBase::TickProjectileMovement(float DeltaTime)
{
}

void AWK_ProjectileBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector DesiredDir = CalculateDesiredMoveDir();
	if (DesiredDir.IsNearlyZero())
	{
		Destroy();
		return;
	}

	// 초기화 
	if (CurrentMoveDir.IsNearlyZero())
	{
		CurrentMoveDir = GetActorForwardVector();
		CurrentMoveDir.Z = 0.f;
		CurrentMoveDir = CurrentMoveDir.GetSafeNormal();
	}
	
	if (bHoming && bGround)
	{
		//  타겟 방향 구하기
		

		const float Dot = FVector::DotProduct(CurrentMoveDir, DesiredDir);
		const bool bTargetBehind = (Dot < BehindDotThreshold);

		if (bTargetBehind)
		{
			// 뒤에 있는 시간이 누적되면 파괴
			BehindTimeAccum += DeltaSeconds;
			if (BehindTimeAccum >= BehindDestroyDelay)
			{
				Destroy();
				return;
			}
		}
		else
		{
			// 다시 앞쪽으로 오면 누적 시간 리셋
			BehindTimeAccum = 0.f;

			// 방향 꺾기 
			const float CurrentYaw = CurrentMoveDir.Rotation().Yaw;
			const float DesiredYaw = DesiredDir.Rotation().Yaw;

			const float MaxDeltaYaw = TurnSpeedDegPerSec * DeltaSeconds;
			const float DeltaYaw = FMath::FindDeltaAngleDegrees(CurrentYaw, DesiredYaw);
			const float ClampedDeltaYaw = FMath::Clamp(DeltaYaw, -MaxDeltaYaw, MaxDeltaYaw);

			CurrentMoveDir = CurrentMoveDir.RotateAngleAxis(ClampedDeltaYaw, FVector::UpVector);
			CurrentMoveDir.Z = 0.f;
			CurrentMoveDir.Normalize();
		}
		SetActorRotation(FRotator(0.f, CurrentMoveDir.Rotation().Yaw, 0.f));

		//  이동 후보 계산
		const FVector CurrentLoc = GetActorLocation();
		const FVector Candidate = CurrentLoc + (CurrentMoveDir * MoveSpeed * DeltaSeconds);


		// 지면 스냅
		FHitResult OuHit;
		FVector LocToGround;
		bool bSnapToGround = SnapToGround(Candidate, LocToGround,OuHit);
		if (!bSnapToGround)
		{
			Destroyed();
			return;
		}
		FVector FinalLoc = LocToGround;
		SetActorLocation(FinalLoc);
	}
	else if (bHoming)
	{
		
	}
	else if (bGround)
	{
		//  이동 후보 계산
		const FVector CurrentLoc = GetActorLocation();
		const FVector Candidate = CurrentLoc + (CurrentMoveDir * MoveSpeed * DeltaSeconds);
		FHitResult OuHit;
		FVector LocToGround;
		bool bSnapToGround = SnapToGround(Candidate, LocToGround,OuHit);
		if (!bSnapToGround)
		{
			Destroyed();
			return;
		}
		FVector FinalLoc = LocToGround;
		SetActorLocation(FinalLoc);
	}
	else
	{
		//  이동 후보 계산
		const FVector CurrentLoc = GetActorLocation();
		const FVector NextLoc = CurrentLoc + (CurrentMoveDir * MoveSpeed * DeltaSeconds);
		SetActorLocation(NextLoc);
	}
}

// Called when the game starts or when spawned
void AWK_ProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AWK_ProjectileBase::OnSphereOverlap);

	CurrentMoveDir = GetActorForwardVector();
	CurrentMoveDir.Z = 0.f;
	CurrentMoveDir = CurrentMoveDir.GetSafeNormal();

	AudioComp->SetSound(ElectricSound);
}

void AWK_ProjectileBase::OnHit()
{
}

void AWK_ProjectileBase::Destroyed()
{
	Super::Destroyed();
}

void AWK_ProjectileBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValidOverlap(OtherActor)) return;
	
	if (!OtherActor->Implements<UWK_PawnCombatInterface>()) return;

	FGameplayEventData Data;

	if (UWK_BlueprintFunctionLibrary::ActorHasTag(OtherActor, WKGameplayTags::Player_Status_Parry))
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, WKGameplayTags::Event_Player_ParrySuccess , Data);
		Destroy();
		return;
	}
	
	Data.Instigator = GetOwner();
	Data.Target = OtherActor;
	
	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	FGameplayEffectContextHandle ContextHandle = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner())->MakeEffectContext();
	ContextHandle.AddSourceObject(GetOwner()); 
	ContextHandle.AddInstigator(GetOwner(),GetOwner());
	FGameplayEffectSpecHandle DamageSpec = OwnerASC->MakeOutgoingSpec(DamageEffectClass, 1.f, ContextHandle);
	if (!DamageSpec.IsValid()) return;
	
	DamageSpec.Data->SetSetByCallerMagnitude(WKGameplayTags::SetByCaller_Shared_BaseDamage, Damage);
	
	if (UWK_BlueprintFunctionLibrary::ActorHasTag(OtherActor, WKGameplayTags::Player_Status_Invincible))
	{
		if (UWK_BlueprintFunctionLibrary::ActorHasTag(OtherActor, WKGameplayTags::Player_Status_PerfectDodge))
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, WKGameplayTags::Event_Player_PerfectDodge , Data);
		}
		return;
	}
	UWK_BlueprintFunctionLibrary::NativeApplyEffectToTarget(OtherActor, DamageSpec);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, WKGameplayTags::Event_Shared_Hit_React_Light , Data);

	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,HitNiagaraSystem,
		GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());
	Destroy();
}

FVector AWK_ProjectileBase::CalculateDesiredMoveDir() const
{
	if (!IsValid(HomingTarget)) return FVector::ZeroVector;

	FVector ToTarget = HomingTarget->GetActorLocation() - GetActorLocation();
	ToTarget.Z = 0.f;
	return ToTarget.GetSafeNormal();
}

bool AWK_ProjectileBase::SnapToGround(const FVector& InCandidate, FVector& OutSnapped, FHitResult& OutHit) const
{
	UWorld* World = GetWorld();
	if (!World) return false;

	const FVector Start = InCandidate + FVector(0, 0, TraceUp);
	const FVector End   = InCandidate - FVector(0, 0, TraceDown);


	// Unreal의 통계/프로파일링 시스템에 찍히는 이름
	//stat collision, stat game 같은 명령어에서 확인 가능
	FCollisionQueryParams Params(SCENE_QUERY_STAT(GroundSnap), false, this);
	Params.AddIgnoredActor(this);
	if (AActor* OwnerActor = GetOwner())
	{
		Params.AddIgnoredActor(OwnerActor);
	}

	const bool bHit = World->LineTraceSingleByChannel(
		OutHit, Start, End, GroundTraceChannel, Params
	);

	if (!bHit) return false;
	if (OutHit.ImpactPoint.Z > GroundHeightThreshold) return false;
	
	OutSnapped = InCandidate;
	OutSnapped.Z = OutHit.ImpactPoint.Z + GroundOffset;
	return true;
}



