#include "Actions/WK_AsyncTaskCooldownChanged.h"

UWK_AsyncTaskCooldownChanged* UWK_AsyncTaskCooldownChanged::Listen(UAbilitySystemComponent* InASC, FGameplayTagContainer InCooldownTags)
{
	if (!IsValid(InASC) || InCooldownTags.Num() == 0)
	{
		return nullptr;
	}

	UWK_AsyncTaskCooldownChanged* Task = NewObject<UWK_AsyncTaskCooldownChanged>();
	Task->ASC = InASC;
	Task->CooldownTags = InCooldownTags;

	InASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(Task, &UWK_AsyncTaskCooldownChanged::OnGEAdded);

	TArray<FGameplayTag> Tags;
	InCooldownTags.GetGameplayTagArray(Tags);
	for (const FGameplayTag& Tag : Tags)
	{
		InASC->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::NewOrRemoved)
			.AddUObject(Task, &UWK_AsyncTaskCooldownChanged::OnTagChanged);
	}

	return Task;
}

void UWK_AsyncTaskCooldownChanged::EndTask()
{
	if (ASC)
	{
		ASC->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);

		TArray<FGameplayTag> Tags;
		CooldownTags.GetGameplayTagArray(Tags);
		for (const FGameplayTag& Tag : Tags)
		{
			ASC->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::NewOrRemoved)
				.RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UWK_AsyncTaskCooldownChanged::OnGEAdded(UAbilitySystemComponent* Target, const FGameplayEffectSpec& Spec, FActiveGameplayEffectHandle Handle)
{
	FGameplayTagContainer AssetTags;
	FGameplayTagContainer GrantedTags;
	Spec.GetAllAssetTags(AssetTags);
	Spec.GetAllGrantedTags(GrantedTags);

	TArray<FGameplayTag> WatchTags;
	CooldownTags.GetGameplayTagArray(WatchTags);

	for (const FGameplayTag& CooldownTag : WatchTags)
	{
		if (!AssetTags.HasTagExact(CooldownTag) && !GrantedTags.HasTagExact(CooldownTag))
		{
			continue;
		}

		float Remaining = 0.f, Total = 0.f;
		if (GetRemainingAndTotal(CooldownTag, Remaining, Total))
		{
			OnBegin.Broadcast(CooldownTag, Total, Remaining);
		}
	}
}

void UWK_AsyncTaskCooldownChanged::OnTagChanged(FGameplayTag Tag, int32 NewCount)
{
	if (NewCount == 0)
	{
		// 끝날 때는 Remaining/Total 굳이 계산할 필요 없음
		OnEnd.Broadcast(Tag, 0.f, 0.f);
	}
}

bool UWK_AsyncTaskCooldownChanged::GetRemainingAndTotal(const FGameplayTag& CooldownTag, float& OutRemaining, float& OutTotal) const
{
	if (!ASC) return false;

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(CooldownTag);

	FGameplayEffectQuery Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(TagContainer);
	TArray<TPair<float, float>> Results = ASC->GetActiveEffectsTimeRemainingAndDuration(Query);

	if (Results.Num() == 0) return false;

	// 가장 오래 남은 쿨다운 선택
	int32 BestIdx = 0;
	for (int32 i = 1; i < Results.Num(); ++i)
	{
		if (Results[i].Key > Results[BestIdx].Key)
		{
			BestIdx = i;
		}
	}

	OutRemaining = Results[BestIdx].Key;
	OutTotal     = Results[BestIdx].Value;
	return true;
}
