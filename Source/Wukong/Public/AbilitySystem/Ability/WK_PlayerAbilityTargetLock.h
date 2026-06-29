// // Fill out your copyright notice in the Description page of Project Settings.
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "WK_PlayerGameplayAbility.h"
// #include "WK_PlayerAbilityTargetLock.generated.h"
//
// /**
//  * 
//  */
// UCLASS()
// class WUKONG_API UWK_PlayerAbilityTargetLock : public UWK_PlayerGameplayAbility
// {
// 	GENERATED_BODY()
// public:
// 	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
// 	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
//
// 	UFUNCTION(BlueprintCallable, Category = "Tick")
// 	void UpdateWidgetPosition(float DeltaTime);
// private:
// 	void TryLockOnTarget();
// 	void FindAvailableActors();
// 	AActor* FindNearestTargetInAvailableActors();
// 	void DrawTargetLockWidget();
// 	void SetWidgetLocation();
//
// 	void CleanUp();
// 	void CancelTargetLockAbility();
//
// 	UPROPERTY(EditAnywhere, Category="Target Lock")
// 	FVector DetectionRange = FVector(2000,2000,300);
// 	
// 	UPROPERTY(EditAnywhere, Category="Target Lock")
// 	float SphereSize =2000;
// 	
// 	UPROPERTY(EditAnywhere, Category="Target Lock")
// 	bool bDrawDebugType = true;
//
// 	UPROPERTY(EditAnywhere, Category="Target Lock")
// 	TArray<TEnumAsByte<EObjectTypeQuery>>  ObjectTypesToSearch;
//
// 	UPROPERTY(EditAnywhere, Category="Target Lock")
// 	TSubclassOf<UUserWidget>  TargetLockWidgetClass;
//
// 	UPROPERTY()
// 	UUserWidget* TargetLockWidget;
// 	
// 	UPROPERTY()
// 	float CachedMaxWalkSpeed;
// 	
// 	UPROPERTY()
// 	TArray<AActor*> AvailableActors;
//
// 	UPROPERTY()
// 	AActor* CurrentNearestTarget;
//
// 	UPROPERTY()
// 	float DistanceToTarget;
//
// 	UPROPERTY()
// 	FVector2D WidgetSize = FVector2D::ZeroVector;
// };
//
//
