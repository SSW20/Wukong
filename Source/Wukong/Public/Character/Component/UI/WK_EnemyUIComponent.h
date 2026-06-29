// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WK_PawnUIComponent.h"
#include "WK_EnemyUIComponent.generated.h"


class UWK_WidgetBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWK_EnemyUIComponent : public UWK_PawnUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterWidget(UWK_WidgetBase* Widget);
	
	UFUNCTION(BlueprintCallable)
	void ClearRegisteredWidget();
private:
	TArray<UWK_WidgetBase*> DrawnWidgets; 
};
