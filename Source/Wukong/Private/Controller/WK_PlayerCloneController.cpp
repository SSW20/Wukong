// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/WK_PlayerCloneController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"


class UCrowdFollowingComponent;

AWK_PlayerCloneController::AWK_PlayerCloneController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("CloneSenseConfig_Sight");

	// 적 진영 = 감지 , 아군 / 중립 진영 = 감지 하지 않음
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;

	// 시야 범위 5000.f , LoseSightRadius = 0 일 경우 감지된 대상을 놓치지 않음 , 시야각 360도
	AISenseConfig_Sight->SightRadius = 5000.f;
	AISenseConfig_Sight->LoseSightRadius = 0.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;
	
	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("ClonePerceptionComponent");

	// 위에 시야 설정을 적용
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);

	// 주요 감지 기능을 시야 기능으로 설정
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());

	// 대상을 감지하거나 놓쳤을 때의 콜백함수
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this,&ThisClass::OnClonePerceptionUpdated);

	// Team Id 정하기, 플레이어와 똑같이
	SetGenericTeamId(FGenericTeamId(0));
}

void AWK_PlayerCloneController::OnClonePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (!BlackboardComponent->GetValueAsObject("TargetActor"))
		{
			if (Actor && Stimulus.WasSuccessfullySensed())
			{
				BlackboardComponent->SetValueAsObject("TargetActor", Actor);
			}
		}
	}
}

ETeamAttitude::Type AWK_PlayerCloneController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* OtherPawn = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());

	if (OtherTeamAgent && OtherPawn)
	{
		//Player, Clone = 0 / Enemy = 1  / Neutral = 2
		return OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId() ? ETeamAttitude::Hostile : ETeamAttitude::Friendly;
	}
	return ETeamAttitude::Friendly;
}

// Called when the game starts or when spawned
void AWK_PlayerCloneController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UCrowdFollowingComponent* PathComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		PathComp->SetCrowdSimulationState(bEnableDetourAvoidance? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourAvoidanceQuality)
		{
		case 1:
			PathComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low); break;
		case 2:
			PathComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium); break;
		case 3:
			PathComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good); break;
		case 4:
			PathComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High); break;
		default: break;
		}

		PathComp->SetAvoidanceGroup(1);
		PathComp->SetGroupsToAvoid(1);
		PathComp->SetCrowdCollisionQueryRange(DetourAvoidanceRange);
	}
}

// Called every frame
void AWK_PlayerCloneController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

