// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/WK_PawnComponentBase.h"
#include "Components/ActorComponent.h"
#include "WK_PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPercentChanged, float, NewPercent);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWK_PawnUIComponent : public UWK_PawnComponentBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FPercentChanged OnHealthChanged;
};
