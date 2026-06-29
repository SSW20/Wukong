// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WK_PawnCombatInterface.generated.h"

class UWK_PawnCombatComponent;
class UWK_PlayerTargetLockComponent;
class UWK_PlayerComboComponent;
class UWK_PlayerUIComponent;
class UWK_PawnUIComponent;
// This class does not need to be modified.
UINTERFACE()
class UWK_PawnCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WUKONG_API IWK_PawnCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UWK_PlayerComboComponent* GetPlayerComboComponent();
	virtual UWK_PlayerTargetLockComponent* GetPlayerTargetLockComponent();
	virtual UWK_PawnCombatComponent* GetPawnCombatComponent() = 0;
};
