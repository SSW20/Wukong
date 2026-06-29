// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RotateFaceToTarget.generated.h"

/**
 * 
 */
UCLASS()
class WUKONG_API UBTTask_RotateFaceToTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_RotateFaceToTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category="FaceTarget")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category="FaceTarget")
	FBlackboardKeySelector SelfActorKey;

	UPROPERTY(EditAnywhere, Category="FaceTarget")
	float AnglePrecisionDeg = 10.f;

	UPROPERTY(EditAnywhere, Category="FaceTarget")
	float InterpSpeed = 8.f;

private:
	bool IsFacing(AActor* Enemy, AActor* Target) const;
	void RotateStep(AActor* Enemy, AActor* Target, float DeltaSeconds) const;
};