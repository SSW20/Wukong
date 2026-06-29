// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "WK_EnemyController.generated.h"

class UAISenseConfig_Sight;
struct FAIStimulus;

UCLASS()
class WUKONG_API AWK_EnemyController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWK_EnemyController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* EnemySenseConfig_Sight;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// AI 감지 컴포넌트 에서의 콜백 함수
	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
