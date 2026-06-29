// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/WK_PawnComponentBase.h"
#include "Components/ActorComponent.h"
#include "WK_PlayerTargetLockComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetLockOn, bool, LockActivate);

class AWK_PlayerController;
class AWK_PlayerCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWK_PlayerTargetLockComponent : public UWK_PawnComponentBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWK_PlayerTargetLockComponent();

	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentNearestTarget() const {return CurrentNearestTarget;};	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float DetectDistance = 1000.f;

	UPROPERTY(BlueprintAssignable)
	FTargetLockOn TargetLockOnDelegate;

	UFUNCTION(BlueprintCallable)
	void ActivateTargetLock();
	
	UFUNCTION(BlueprintCallable)
	void CancelTargetLock();

private:

	void FindAvailableActors();
	AActor* FindNearestTargetInAvailableActors();
	void DrawTargetLockWidget();
	void SetWidgetLocation();
	void UpdateCameraRotation(float DeltaTime);
	void UpdatePlayerRotation(float DeltaTime);
	void Clean();
	bool CheckIsValid();
	UPROPERTY(EditAnywhere, Category="Target Lock")
	float SphereSize =2000;
	
	UPROPERTY(EditAnywhere, Category="Target Lock")
	bool bDrawDebugType = true;

	UPROPERTY(EditAnywhere, Category="Target Lock")
	TArray<TEnumAsByte<EObjectTypeQuery>>  ObjectTypesToSearch;

	UPROPERTY(EditAnywhere, Category="Target Lock")
	TSubclassOf<UUserWidget>  TargetLockWidgetClass;

	UPROPERTY()
	UUserWidget* TargetLockWidget;
	
	UPROPERTY()
	TArray<AActor*> AvailableActors;

	UPROPERTY()
	AActor* CurrentNearestTarget;

	UPROPERTY()
	float DistanceToTarget;

	UPROPERTY()
	FVector2D WidgetSize = FVector2D::ZeroVector;

	UPROPERTY()
	AWK_PlayerCharacter* Owner;

	UPROPERTY()
	AWK_PlayerController* OwnerController;
};
