// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/ANS_UpdateActorRotation.h"

#include "AIController.h"
#include "MotionWarpingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/WK_EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UANS_UpdateActorRotation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration,EventReference);

	if (!MeshComp) return;

	AWK_BaseCharacter* OwnerCharacter = Cast<AWK_BaseCharacter>(MeshComp->GetOwner());
	CachedCharacter = OwnerCharacter;

	
	if (OwnerCharacter && !BlackboardTargetKey.IsNone())
	{
		if (AAIController* AIC = Cast<AAIController>(OwnerCharacter->GetController()))
		{
			if (UBlackboardComponent* BB = AIC->GetBlackboardComponent())
			{
				UObject* Obj = BB->GetValueAsObject(BlackboardTargetKey);
				if (AActor* Actor = Cast<AActor>(Obj))
				{
					CachedTarget = Actor;
				}
			}
		}
	}

	// if (!CachedTarget.IsValid())
	// {
	// 	if (UWorld* World = OwnerCharacter ? OwnerCharacter->GetWorld() : nullptr)
	// 	{
	// 		CachedTarget = UGameplayStatics::GetPlayerCharacter(World, 0);
	// 	}
	// }
}

void UANS_UpdateActorRotation::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime,EventReference);
	UpdateWarpTarget(MeshComp, FrameDeltaTime);

}

void UANS_UpdateActorRotation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation,EventReference);
	CachedCharacter.Reset();
	CachedTarget.Reset();
	LastRot = FRotator::ZeroRotator;
}


void UANS_UpdateActorRotation::UpdateWarpTarget(USkeletalMeshComponent* MeshComp, float DeltaTime)
{
	if (!MeshComp) return;

	AWK_BaseCharacter* OwnerCharacter = CachedCharacter.Get();
	if (!OwnerCharacter) return;
	
	UMotionWarpingComponent* MW = OwnerCharacter->GetMotionWarpingComponent();
	if (!MW) return;
	
	CheckTargetChanged();
	
	AActor* Target = CachedTarget.Get();
	if (!Target) return;

	
	const FVector OwnerLoc  = OwnerCharacter->GetActorLocation();
	const FVector TargetLoc = Target->GetActorLocation();

	FRotator Desired = UKismetMathLibrary::FindLookAtRotation(OwnerLoc, TargetLoc);
	Desired.Pitch = 0.f;
	Desired.Roll  = 0.f;

	FRotator Current = OwnerCharacter->GetActorRotation();
	Current.Pitch = 0.f;
	Current.Roll  = 0.f;


	FRotator NewRot = FMath::RInterpConstantTo(Current, Desired, DeltaTime, Speed);

	OwnerCharacter->SetActorRotation(NewRot);
}

void UANS_UpdateActorRotation::CheckTargetChanged()
{
	if (!CachedTarget.IsValid()) return;
	
	if (AAIController* AIC = Cast<AAIController>(CachedCharacter->GetController()))
	{
		if (UBlackboardComponent* BB = AIC->GetBlackboardComponent())
		{
			UObject* Obj = BB->GetValueAsObject(BlackboardTargetKey);
			if (Obj != CachedTarget)
			{
				CachedTarget = Cast<AActor>(Obj);
			}
		}
	}
	
}
