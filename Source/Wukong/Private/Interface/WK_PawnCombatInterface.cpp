// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/WK_PawnCombatInterface.h"


// Add default functionality here for any IWK_PawnCombatInterface functions that are not pure virtual.
UWK_PlayerComboComponent* IWK_PawnCombatInterface::GetPlayerComboComponent()
{
	return nullptr;
}

UWK_PlayerTargetLockComponent* IWK_PawnCombatInterface::GetPlayerTargetLockComponent()
{
	return nullptr;
}
