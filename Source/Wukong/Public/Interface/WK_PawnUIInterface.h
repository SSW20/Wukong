// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WK_PawnUIInterface.generated.h"

class UWK_PawnUIComponent;
class UWK_PlayerUIComponent;
class UWK_EnemyUIComponent;
// This class does not need to be modified.
UINTERFACE()
class UWK_PawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WUKONG_API IWK_PawnUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UWK_PawnUIComponent* GetPawnUIComponent() const = 0;

	virtual UWK_PlayerUIComponent* GetPlayerUIComponent() const;
	
	virtual UWK_EnemyUIComponent* GetEnemyUIComponent() const;
};
