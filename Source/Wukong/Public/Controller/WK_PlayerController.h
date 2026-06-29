// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Controller.h"
#include "WK_PlayerController.generated.h"

UCLASS()
class WUKONG_API AWK_PlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWK_PlayerController();

	virtual FGenericTeamId GetGenericTeamId() const override { return PlayerGenericTeamId; }

private:
	FGenericTeamId PlayerGenericTeamId;
};
