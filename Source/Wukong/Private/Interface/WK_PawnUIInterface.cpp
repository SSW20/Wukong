// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/WK_PawnUIInterface.h"


// Add default functionality here for any IWK_PawnUIInterface functions that are not pure virtual.
UWK_PlayerUIComponent* IWK_PawnUIInterface::GetPlayerUIComponent() const
{
	return nullptr;
}

UWK_EnemyUIComponent* IWK_PawnUIInterface::GetEnemyUIComponent() const
{
	return nullptr;
}

