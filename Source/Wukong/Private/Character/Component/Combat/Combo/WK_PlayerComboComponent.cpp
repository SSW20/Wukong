// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/Combat/Combo/WK_PlayerComboComponent.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "WK_BlueprintFunctionLibrary.h"
#include "WK_GameplayTags.h"
#include "AbilitySystem/WK_AbilitySystemComponent.h"
#include "Character/WK_PlayerCharacter.h"
#include "Character/Component/UI/WK_PlayerUIComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Wukong/WK_DebugHelper.h"


// Sets default values for this component's properties
UWK_PlayerComboComponent::UWK_PlayerComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UWK_PlayerComboComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<AWK_PlayerCharacter>(GetOwner());
}

void UWK_PlayerComboComponent::OnWeaponGaugeMax()
{
	AWK_PlayerCharacter* Player = Cast<AWK_PlayerCharacter>(GetOwner());
	WeaponEndNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(WeaponEndNiagaraSystem, Player->GetMesh(), FName("WeaponEndSocket"),
		FVector(0, 0, 0), FRotator(0, 0, 0), EAttachLocation::Type::SnapToTarget, true);
		
	WeaponStartNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(WeaponStartNiagaraSystem, Player->GetMesh(), FName("WeaponStartSocket"),
		FVector(0, 0, 0), FRotator(0, 0, 0), EAttachLocation::Type::SnapToTarget, true);

	WeaponEndNiagaraComponent->SetFloatParameter("_Size", InitialNiagaraSystemSize + CurrentChargedAttackComboIndex * IncreaseNiagaraSystemSizeScale);
	WeaponStartNiagaraComponent->SetFloatParameter("_Size", InitialNiagaraSystemSize + CurrentChargedAttackComboIndex * IncreaseNiagaraSystemSizeScale);

	UGameplayStatics::PlaySoundAtLocation(this,GaugeMaxSound,GetOwner()->GetActorLocation());
}


void UWK_PlayerComboComponent::RegisterAttackInput(const FGameplayTag& InputTag)
{
	if (UWK_BlueprintFunctionLibrary::ActorHasTag(Owner, WKGameplayTags::Player_Status_BlockInput)) return;
	{
		if (bNextLightAttack)
		{
			CurrentLightComboIndex = (CurrentLightComboIndex + 1) % LightComboAbilities.Num();
			Owner->GetWKAbilitySystemComponent()->TryActivateAbilityByClass(LightComboAbilities[CurrentLightComboIndex]);
		}
		else
		{
			ResetLightCombo();
			CurrentLightComboIndex = 0;
			Owner->GetWKAbilitySystemComponent()->TryActivateAbilityByClass(LightComboAbilities[CurrentLightComboIndex]);
		}
	}
}

void UWK_PlayerComboComponent::RegisterDodgeInput(const FGameplayTag& InputTag)
{
	// 나중에 토글 모드 할 떄 
	bool bTargetLock = UWK_BlueprintFunctionLibrary::ActorHasTag(Owner, WKGameplayTags::Player_Status_TargetLock);
	
	EActorDirection ActorDirection = UWK_BlueprintFunctionLibrary::CalculateActorDirection(Owner, CurrentDodgeDirection, bTargetLock);

	TSubclassOf<UGameplayAbility> DodgeAbilityClass = FindActorDodgeAbility(ActorDirection);
	
	if (UWK_BlueprintFunctionLibrary::ActorHasTag(Owner, WKGameplayTags::Player_Status_BlockInput)) return;
	{
		if (bNextDodge)
		{
			CurrentDodgeComboIndex = (CurrentDodgeComboIndex + 1) % DodgeComboMontages;
			Owner->GetWKAbilitySystemComponent()->TryActivateAbilityByClass(DodgeAbilityClass);
		}
		else
		{
			ResetDodgeCombo();
			CurrentDodgeComboIndex = 0;
			Owner->GetWKAbilitySystemComponent()->TryActivateAbilityByClass(DodgeAbilityClass);

		}
	}
}

void UWK_PlayerComboComponent::ResetLightCombo()
{
	CurrentLightComboIndex = -1;
}

void UWK_PlayerComboComponent::ResetDodgeCombo()
{
	CurrentDodgeComboIndex = -1;
}



TSubclassOf<UGameplayAbility> UWK_PlayerComboComponent::FindActorDodgeAbility(const EActorDirection& ActorDir)
{
	for (FActorDodgeAbility& DodgeAbility : DodgeComboAbilities)
	{
		if (DodgeAbility.Direction == ActorDir) return (DodgeAbility.Ability);
	}
	return nullptr;
}

void UWK_PlayerComboComponent::SetCurrentChargedAttackComboIndex(int32 NewCount)
{
	CurrentChargedAttackComboIndex = NewCount;
	if (NewCount == 0)
	{
		Owner->GetPlayerUIComponent()->OnGaugePointChanged.Broadcast(0);
	}
}


