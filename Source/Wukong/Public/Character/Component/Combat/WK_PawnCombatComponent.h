// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/WK_PawnComponentBase.h"
#include "Components/ActorComponent.h"
#include "WK_PawnCombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWK_PawnCombatComponent : public UWK_PawnComponentBase
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void ToggleCollision(bool bShouldEnable, bool bFoot, FName CollisionStartLeft = FName("None"), FName CollisionStartRight = FName("None"));

	virtual void WeaponHitBegin(AActor* TargetActor);
	virtual void WeaponHitEnd(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void SetUpdateCollision(bool bShouldEnable) {bUpdateWeaponCollision = bShouldEnable;}
protected:
	TArray<AActor*> OverlappedActors;

	bool bUpdateWeaponCollision = false;
};
