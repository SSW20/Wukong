// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WK_InputDataConfig.h"

const UInputAction* UWK_InputDataConfig::FindMoveInputActionByTag(const FGameplayTag& InputTag) const
{
	if (InputTag.IsValid())
	{
		for (const FWK_InputActionConfig& InputActionConfig : MoveInputActionConfigs)
		{
			if (InputActionConfig.InputTag.MatchesTagExact(InputTag))
			{
				return InputActionConfig.InputAction;
			}
		}
	}
	return nullptr;
}
