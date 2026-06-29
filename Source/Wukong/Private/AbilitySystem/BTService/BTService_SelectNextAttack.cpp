// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BTService/BTService_SelectNextAttack.h"

#include "AIController.h"
#include "WK_BlueprintFunctionLibrary.h"
#include "WK_GameplayTags.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/WK_EnemyCharacter.h"
#include "Data/WK_EnemyAttackPool.h"
#include "Wukong/WK_DebugHelper.h"


UBTTask_SelectNextAttack::UBTTask_SelectNextAttack()
{
	NodeName = FString("Native Select Next Attack");
}


EBTNodeResult::Type UBTTask_SelectNextAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;
	
	AWK_EnemyCharacter* Enemy =  Cast<AWK_EnemyCharacter>(BB->GetValueAsObject(SelfActorKey.SelectedKeyName));
	AActor* Target = Cast<AActor>(BB->GetValueAsObject(TargetActorKey.SelectedKeyName));

	if (BB->GetValueAsBool(bAttacking.SelectedKeyName)) return EBTNodeResult::Succeeded;;
	if (Target == nullptr ) return EBTNodeResult::Failed;
	if (UWK_BlueprintFunctionLibrary::ActorHasTag(Target, WKGameplayTags::Shared_Status_Death))
	{
		BB->SetValueAsBool(bTargetDead.SelectedKeyName, true);
	}
	float Dist = FVector::Distance(Enemy->GetActorLocation(), Target->GetActorLocation());
	BB->SetValueAsFloat(DistanceToTarget.SelectedKeyName, Dist);

	UWK_EnemyAttackPool* AttackPoolData = Enemy->GetEnemyAttackPoolData();

	if (!IsValid(Target)) return EBTNodeResult::Failed;
	FVector ToTarget = Target->GetActorLocation() - Enemy->GetActorLocation();
	ToTarget.Z = 0.f;

	FVector D = ToTarget.GetSafeNormal();

	FVector F2 = Enemy->GetActorForwardVector();
	F2.Z = 0.f;
	F2.Normalize();

	const float ForwardDot = FVector::DotProduct(F2, D);
	const bool InBack = (ForwardDot < BehindDegree);     // 뒤 120도

	const float CrossZ = FVector::CrossProduct(F2, D).Z;
	const bool InLeft  = (CrossZ < -0.02f);
	
	TArray<FGameplayTag> CandidateTags;
	for (FEnemyAttackData Data : AttackPoolData->AttackPool)
	{
		if (!Data.AbilityTag.IsValid()) continue;
		if (UWK_BlueprintFunctionLibrary::ActorHasTag(Enemy, Data.CoolDownTag)) continue;
		if (Data.MaxDistance < Dist || Data.MinDistance > Dist) continue;

		// 가까이 있고 뒤에 있을 떄  왼쪽 6번과 오른쪽 7번
		if (Data.AbilityTag.MatchesTagExact(WKGameplayTags::Enemy_TD_Ability_Attack06) && InBack && InLeft)
		{
			BB->SetValueAsName(SelectedAttackAbilityTag.SelectedKeyName, Data.AbilityTag.GetTagName());
			BB->SetValueAsName(LatestAttackAbilityTag.SelectedKeyName, Data.AbilityTag.GetTagName());
			BB->SetValueAsBool(CanAttack.SelectedKeyName, true);
			CandidateTags.Empty();
			return EBTNodeResult::Succeeded;
		}
		if (Data.AbilityTag.MatchesTagExact(WKGameplayTags::Enemy_TD_Ability_Attack07) &&  InBack && !InLeft)
		{
			BB->SetValueAsName(SelectedAttackAbilityTag.SelectedKeyName, Data.AbilityTag.GetTagName());
			BB->SetValueAsName(LatestAttackAbilityTag.SelectedKeyName, Data.AbilityTag.GetTagName());
			BB->SetValueAsBool(CanAttack.SelectedKeyName, true);
			CandidateTags.Empty();
			return EBTNodeResult::Succeeded;
		}
		if (!Data.AbilityTag.MatchesTagExact(WKGameplayTags::Enemy_TD_Ability_Attack07) &&
			!Data.AbilityTag.MatchesTagExact(WKGameplayTags::Enemy_TD_Ability_Attack06))
		{
			CandidateTags.AddUnique(Data.AbilityTag);
		}
	}
	
	if (CandidateTags.Num() == 0)
	{
		BB->ClearValue(LatestAttackAbilityTag.SelectedKeyName);
		BB->ClearValue(SelectedAttackAbilityTag.SelectedKeyName);
		BB->SetValueAsBool(CanAttack.SelectedKeyName, false);
		return EBTNodeResult::Succeeded;
	}
	
	int32 idx = FMath::RandRange(0, CandidateTags.Num() - 1);
	BB->SetValueAsName(SelectedAttackAbilityTag.SelectedKeyName, CandidateTags[idx].GetTagName());
	BB->SetValueAsName(LatestAttackAbilityTag.SelectedKeyName, CandidateTags[idx].GetTagName());
	BB->SetValueAsBool(CanAttack.SelectedKeyName, true);
	CandidateTags.Empty();
	return EBTNodeResult::Succeeded;
}
