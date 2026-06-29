// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BTService/BTTask_RotateFaceToTarget.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnitConversion.h"

UBTTask_RotateFaceToTarget::UBTTask_RotateFaceToTarget()
{
	NodeName = TEXT("Rotate To Face Target");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RotateFaceToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	AActor* Target = Cast<AActor>(BB->GetValueAsObject(TargetActorKey.SelectedKeyName));
	AActor* Enemy = Cast<AActor>(BB->GetValueAsObject(SelfActorKey.SelectedKeyName));

	if (!Enemy || !Target) return EBTNodeResult::Failed;

	if (IsFacing(Enemy, Target)) return EBTNodeResult::Succeeded;

	return EBTNodeResult::InProgress;
}

void UBTTask_RotateFaceToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	AActor* Target = Cast<AActor>(BB->GetValueAsObject(TargetActorKey.SelectedKeyName));
	AActor* Enemy = Cast<AActor>(BB->GetValueAsObject(SelfActorKey.SelectedKeyName));

	if (!Enemy || !Target)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (IsFacing(Enemy, Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}
	RotateStep(Enemy, Target, DeltaSeconds);
}

bool UBTTask_RotateFaceToTarget::IsFacing(AActor* Enemy, AActor* Target) const
{
	const FVector EnemyFwd = Enemy->GetActorForwardVector().GetSafeNormal2D();
	FVector ToTarget = (Enemy->GetActorLocation() - Target->GetActorLocation());
	ToTarget.Z =0.f;
	ToTarget.Normalize();

	float DotVal = FVector::DotProduct(EnemyFwd, ToTarget);
	const float AngleDeg = FMath::Acos(FMath::Clamp(DotVal, -1.f, 1.f));

	return AngleDeg <= AnglePrecisionDeg;
	
}

void UBTTask_RotateFaceToTarget::RotateStep(AActor* Enemy, AActor* Target, float DeltaSeconds) const
{
	const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Enemy->GetActorLocation(), Target->GetActorLocation());
	const FRotator InterpRot = FMath::RInterpTo(Enemy->GetActorRotation(), LookAtRot, DeltaSeconds, InterpSpeed);

	Enemy->SetActorRotation(FRotator(0.f, InterpRot.Yaw, 0.f));
}
