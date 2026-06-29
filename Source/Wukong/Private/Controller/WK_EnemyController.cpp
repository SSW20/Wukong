// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/WK_EnemyController.h"

#include "WK_BlueprintFunctionLibrary.h"
#include "WK_GameplayTags.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"


AWK_EnemyController::AWK_EnemyController()
{
	EnemySenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseConfig_Sight");

	EnemySenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	EnemySenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	EnemySenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;

	EnemySenseConfig_Sight->SightRadius = 5000.f;
	EnemySenseConfig_Sight->LoseSightRadius = 5500.f;
	EnemySenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;

	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");

	EnemyPerceptionComponent->ConfigureSense(*EnemySenseConfig_Sight);

	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AWK_EnemyController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* OtherPawn = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherAgentInterface = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	if (OtherAgentInterface)
	{
		return OtherAgentInterface->GetGenericTeamId() < GetGenericTeamId() ? ETeamAttitude::Hostile : ETeamAttitude::Friendly;	
	}
	return ETeamAttitude::Friendly;
}

// Called when the game starts or when spawned
void AWK_EnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWK_EnemyController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UWK_BlueprintFunctionLibrary::ActorHasTag(Actor, WKGameplayTags::Player_Status_Hide)) return;
	if (UBlackboardComponent* BB = GetBlackboardComponent())
	{
		if (!BB->GetValueAsObject("TargetActor"))
		{
			if (Stimulus.WasSuccessfullySensed() && Actor)
			{
				BB->SetValueAsObject("TargetActor", Actor);
			}
		}
	}
}


