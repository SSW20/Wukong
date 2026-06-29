#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "WK_AsyncTaskCooldownChanged.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnCooldownChanged,
	FGameplayTag, CooldownTag,
	float, TotalTime,
	float, RemainingTime
);

UCLASS(BlueprintType)
class WUKONG_API UWK_AsyncTaskCooldownChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnCooldownChanged OnBegin;

	UPROPERTY(BlueprintAssignable)
	FOnCooldownChanged OnEnd;

	// BP: AsyncTaskCooldownChanged::Listen(ASC, CooldownTags)
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly="true"))
	static UWK_AsyncTaskCooldownChanged* Listen(UAbilitySystemComponent* InASC, FGameplayTagContainer InCooldownTags);

	UFUNCTION(BlueprintCallable)
	void EndTask();

private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;

	FGameplayTagContainer CooldownTags;

	void OnGEAdded(UAbilitySystemComponent* Target, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle);
	void OnTagChanged(FGameplayTag Tag, int32 NewCount);

	bool GetRemainingAndTotal(const FGameplayTag& CooldownTag, float& OutRemaining, float& OutTotal) const;
};
