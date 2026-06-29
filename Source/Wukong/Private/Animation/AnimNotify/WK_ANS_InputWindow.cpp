// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/WK_ANS_InputWindow.h"
#include "Character/WK_BaseCharacter.h"
#include "Character/Component/Combat/Combo/WK_PlayerComboComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Wukong/WK_DebugHelper.h"


void UWK_ANS_InputWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (UWK_PlayerComboComponent* ComboComponent = Owner->FindComponentByClass<UWK_PlayerComboComponent>())
		{
			if (bLightAttack) ComboComponent->bNextLightAttack = true;
			if (bDodge) ComboComponent->bNextDodge = true;
		}
	}
}

void UWK_ANS_InputWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (UWK_PlayerComboComponent* ComboComponent = Owner->FindComponentByClass<UWK_PlayerComboComponent>())
		{
			if (bLightAttack) ComboComponent->bNextLightAttack = false;
			if (bDodge) ComboComponent->bNextDodge = false;
		}
	}
}

