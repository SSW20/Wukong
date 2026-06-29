// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WK_WidgetBase.generated.h"

class UWK_EnemyUIComponent;
class UWK_PlayerUIComponent;
/**
 * 
 */
UCLASS()
class WUKONG_API UWK_WidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	// 위젯이 생성된 후 호출 
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnPlayerUIComponentInitialized"))
	void BP_PlayerUIComponentInitialized(UWK_PlayerUIComponent* PlayerUIComponent); 

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnEnemyUIComponentInitialized"))
	void BP_EnemyUIComponentInitialized(UWK_EnemyUIComponent* EnemyUIComponent); 
	
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyWidget(AActor* EnemyActor);
};

