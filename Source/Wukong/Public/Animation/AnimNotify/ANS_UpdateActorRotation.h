// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_UpdateActorRotation.generated.h"

class AWK_BaseCharacter;
class AWK_PlayerCharacter;
class AWK_EnemyCharacter;
/**
 * 
 */
UCLASS()
class WUKONG_API UANS_UpdateActorRotation : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionWarping")
	FName WarpTargetName = TEXT("TargetActor");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionWarping")
	float RotationInterpSpeed = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionWarping")
	FName BlackboardTargetKey = TEXT("TargetActor");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MotionWarping")
	float Speed = 180.f;
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	// NotifyState 인스턴스별 캐시(서버/싱글 기준)
	TWeakObjectPtr<AWK_BaseCharacter> CachedCharacter;
	TWeakObjectPtr<AActor> CachedTarget;
	FRotator LastRot = FRotator::ZeroRotator;
	
	void UpdateWarpTarget(USkeletalMeshComponent* MeshComp, float DeltaTime);
	void CheckTargetChanged();
};
