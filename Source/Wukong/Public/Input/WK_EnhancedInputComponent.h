#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Data/WK_InputDataConfig.h"
#include "WK_EnhancedInputComponent.generated.h"
/**
 * 
 */
UCLASS()
class WUKONG_API UWK_EnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserObject, typename CallbackFunc>
	void BindMoveInputAction(const UWK_InputDataConfig* InputDataConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent,
		UserObject* UserObj, CallbackFunc Callback);

	template <class UserObject, typename CallbackFunc>
	void BindMoveInputAction(const UWK_InputDataConfig* InputDataConfig, const FGameplayTag& InputTag, UserObject* UserObj,
	CallbackFunc TriggerCallback, CallbackFunc ReleaseCallBack);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UWK_InputDataConfig* InputDataConfig, UserObject* UserObj, CallbackFunc TriggerCallback, CallbackFunc ReleaseCallBack);


};

template <class UserObject, typename CallbackFunc>
void UWK_EnhancedInputComponent::BindMoveInputAction(const UWK_InputDataConfig* InputDataConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserObject* UserObj, CallbackFunc Callback)
{
	checkf(InputDataConfig, TEXT("Invalid InputConfig"));

	if (const UInputAction* FoundAction = InputDataConfig->FindMoveInputActionByTag(InputTag))
	{
		BindAction(FoundAction, TriggerEvent, UserObj, Callback);
	}
}

template <class UserObject, typename CallbackFunc>
void UWK_EnhancedInputComponent::BindMoveInputAction(const UWK_InputDataConfig* InputDataConfig, const FGameplayTag& InputTag, UserObject* UserObj,
	CallbackFunc TriggerCallback, CallbackFunc ReleaseCallBack)
{
	checkf(InputDataConfig, TEXT("Invalid InputConfig"));

	if (const UInputAction* FoundAction = InputDataConfig->FindMoveInputActionByTag(InputTag))
	{
		BindAction(FoundAction, ETriggerEvent::Started, UserObj, TriggerCallback);
		BindAction(FoundAction, ETriggerEvent::Completed, UserObj, ReleaseCallBack);
	}
}


template <class UserObject, typename CallbackFunc>
void UWK_EnhancedInputComponent::BindAbilityInputAction(const UWK_InputDataConfig* InputDataConfig, UserObject* UserObj,
	CallbackFunc TriggerCallback, CallbackFunc ReleaseCallBack)
{
	checkf(InputDataConfig, TEXT("Invalid InputConfig"));

	for (const FWK_InputActionConfig& AbilityAction : InputDataConfig->AbilityInputActionConfigs)
	{
		BindAction(AbilityAction.InputAction, ETriggerEvent::Started, UserObj, TriggerCallback, AbilityAction.InputTag);
		BindAction(AbilityAction.InputAction, ETriggerEvent::Completed, UserObj, ReleaseCallBack, AbilityAction.InputTag);
	}
}
