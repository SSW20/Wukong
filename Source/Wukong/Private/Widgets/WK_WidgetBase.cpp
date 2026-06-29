// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WK_WidgetBase.h"

#include "Character/Component/UI/WK_EnemyUIComponent.h"
#include "Character/Component/UI/WK_PlayerUIComponent.h"
#include "Interface/WK_PawnUIInterface.h"

void UWK_WidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (IWK_PawnUIInterface* PawnUIInterface = Cast<IWK_PawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UWK_PlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_PlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}

void UWK_WidgetBase::InitEnemyWidget(AActor* EnemyActor)
{
	if (IWK_PawnUIInterface* PawnUIInterface = Cast<IWK_PawnUIInterface>(EnemyActor))
	{
		if (UWK_EnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent())
		{
			BP_EnemyUIComponentInitialized(EnemyUIComponent);
		}
	}
}

