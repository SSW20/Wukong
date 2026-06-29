// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Component/Combat/WK_PawnCombatComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/WK_EnumTypes.h"
#include "WK_BlueprintFunctionLibrary.generated.h"

struct FGameplayEffectSpecHandle;
enum class EActorDirection : uint8;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class WUKONG_API UWK_BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static void AddGameplayTagToActor(AActor* Actor, const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable)
	static void RemoveGameplayTagToActor(AActor* Actor, const FGameplayTag& Tag);

	UFUNCTION(BlueprintPure)
	static bool ActorHasTag(AActor* Actor, const FGameplayTag& Tag);

	UFUNCTION(BlueprintCallable)
	static int FindAngleIndex(const float& Angle);

	UFUNCTION(BlueprintCallable)
	static EActorDirection CalculateActorDirection(ACharacter* Character, FVector& Direction, bool bToggle);

	UFUNCTION(BlueprintCallable)
	static int32 CalculateHitReactDirection(AActor* Attacker, AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	static FRotator CalculateActorRotation(AActor* Attacker, AActor* TargetActor);

	static UWK_PawnCombatComponent* NativeGetPawnCombatComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, meta=(DisplayName = "Get Pawn Combat Component From Actor"))
	static UWK_PawnCombatComponent* BP_GetPawnCombatComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static EDistanceToTarget GetDistanceToTarget(float Distance, float TooFar, float Far, float Middle, float Close);

	UFUNCTION(BlueprintPure)
	static FGameplayTag GetTagByName(FName TagName);

	UFUNCTION(BlueprintPure)
	static bool IsTargetHostile(APawn* OwningPawn, APawn* TargetPawn);
	
	static FActiveGameplayEffectHandle NativeApplyEffectToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& SpecHandle);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Effect To Target"))
	static FActiveGameplayEffectHandle BP_ApplyEffectToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& SpecHandle);

	// Custom Latent 뼈대 만들기
	// ExpandEnumAsExecs == enum 블루프린트 노드에서 **여러 개의 개별적인 실행 핀(Execution Pins, Exec Pins)으로 자동으로 확장하도록 언리얼 엔진에게 지시하는 역할
	UFUNCTION(BlueprintCallable, meta =(Latent, WorldContext="WorldContextObject", LatentInfo="LatentInfo",
		ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime,
		ECountDownActionInput CountDownInput, ECountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo, bool bReverse);

	static float GetEnemyAcceptRadius(AActor* Enemy);

	UFUNCTION(BlueprintCallable)
	static TArray<FVector> GetRandomPointInRadius(const FVector& CenterLocation,const FVector& Forward,
	int32 PointCount,float DistanceToCenter);

	UFUNCTION(BlueprintCallable)
	static TArray<FVector> GetRandomPointInLine(const FVector& CenterLocation,const FVector& Direction,const FVector& Forward,
	int32 PointCount,float DistanceByPoints);
};
