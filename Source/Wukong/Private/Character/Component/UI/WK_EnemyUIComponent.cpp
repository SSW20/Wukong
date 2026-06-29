// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/UI/WK_EnemyUIComponent.h"

#include "Widgets/WK_WidgetBase.h"


void UWK_EnemyUIComponent::RegisterWidget(UWK_WidgetBase* Widget)
{
	DrawnWidgets.AddUnique(Widget);
}

void UWK_EnemyUIComponent::ClearRegisteredWidget()
{
	for (UWK_WidgetBase* Widget : DrawnWidgets)
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
		}
	}
}
