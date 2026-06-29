// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WK_PlayerCloneController.generated.h"

class UAISenseConfig_Sight;

UCLASS()
class WUKONG_API AWK_PlayerCloneController : public AAIController
{
	GENERATED_BODY()

public:
	/*
 *	FObjectInitializer는 언리얼 오브젝트가 생성될 때 초기화 데이터를 전달하는 데 사용되는 구조체
 *	이를 통해 부모 클래스(AAIController)의 속성을 초기화하거나 기본 하위 컴포넌트를 설정할 수 있습니다.*/
	AWK_PlayerCloneController(const FObjectInitializer& ObjectInitializer);

	/*	AI 감지 컴포넌트, 이 컴포넌트가 AI의 시야, 청각 등 모든 감지 기능을 총괄 */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	/*	시야 감지 설정 컴포넌트, AI가 "시각"으로 대상을 어떻게 감지할지 구체적인 설정을 담는 역할*/
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	// AI 감지 컴포넌트 에서의 콜백 함수
	UFUNCTION()
	virtual void OnClonePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	// ~ Begin IGenericTeamAgentInterface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	// ~ End IGenericTeamAgentInterface
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Detour 기반의 군중 회피 시스템을 사용할지 여부를 결정하는 변수
	UPROPERTY(EditDefaultsOnly , Category = "Detour Crowd Avoidance Config")
	bool bEnableDetourAvoidance = true;

	// 군중 회피 알고리즘의 정확도와 성능의 균형을 조절하는 변수
	UPROPERTY(EditDefaultsOnly , Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourAvoidance", UIMIN = "1", UIMAX = "4"))
	int32 DetourAvoidanceQuality = 4;

	//다른 객체를 인지하고 회피 기동을 시작하는 최대 거리를 설정
	UPROPERTY(EditDefaultsOnly , Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourAvoidance"))
	float DetourAvoidanceRange = 600.f;
};
