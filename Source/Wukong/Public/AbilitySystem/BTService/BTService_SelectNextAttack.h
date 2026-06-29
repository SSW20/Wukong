// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTService_SelectNextAttack.generated.h"

/**
 * 
 */
UCLASS()
class WUKONG_API UBTTask_SelectNextAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()


public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UBTTask_SelectNextAttack();

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector SelfActorKey;
	
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector CanAttack;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector DistanceToTarget;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector LatestAttackAbilityTag;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector SelectedAttackAbilityTag;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector bAttacking;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector bTargetDead;

	UPROPERTY(EditAnywhere, Category="Degree")
	float BehindDegree = 0.4f;
	
private:
	// bool TargetInBL(const AActor* Enemy, const AActor* Target) const;
	// bool TargetInBR(const AActor* Enemy, const AActor* Target) const;
};
