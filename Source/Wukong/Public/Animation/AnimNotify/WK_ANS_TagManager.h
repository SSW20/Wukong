// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WK_GameplayTags.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "WK_ANS_TagManager.generated.h"

/**
 * 
 */
UCLASS()
class WUKONG_API UWK_ANS_TagManager : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultWalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBlockInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFollow = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFly = false;
};
