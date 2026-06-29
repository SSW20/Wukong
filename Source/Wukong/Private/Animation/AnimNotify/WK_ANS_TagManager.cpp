// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify/WK_ANS_TagManager.h"

#include "WK_BlueprintFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/WK_BaseCharacter.h"
#include "Character/WK_PlayerCharacter.h"

void UWK_ANS_TagManager::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (bBlockInput) UWK_BlueprintFunctionLibrary::AddGameplayTagToActor(Owner, WKGameplayTags::Player_Status_BlockInput);
		if (AWK_PlayerCharacter* BaseCharacter = Cast<AWK_PlayerCharacter>(Owner))
		{
			BaseCharacter->GetCharacterMovement()->MaxWalkSpeed = 0.f;
			if (bFollow) BaseCharacter->SetFollowPelvis(true);
			if (bFly) BaseCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		}
	}

	
}

void UWK_ANS_TagManager::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (bBlockInput) UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(Owner, WKGameplayTags::Player_Status_BlockInput);
		if (AWK_PlayerCharacter* BaseCharacter = Cast<AWK_PlayerCharacter>(Owner))
		{
			BaseCharacter->GetCharacterMovement()->MaxWalkSpeed = 300.f;
			if (bFollow) BaseCharacter->SetFollowPelvis(false);
			if (bFly) BaseCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		}
	}
}
