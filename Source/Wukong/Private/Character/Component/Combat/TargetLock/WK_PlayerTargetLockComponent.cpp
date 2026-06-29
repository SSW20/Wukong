// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/Combat/TargetLock/WK_PlayerTargetLockComponent.h"

#include "WK_BlueprintFunctionLibrary.h"
#include "WK_GameplayTags.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Character/WK_PlayerCharacter.h"
#include "Components/SizeBox.h"
#include "Controller/WK_PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


UWK_PlayerTargetLockComponent::UWK_PlayerTargetLockComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

}


void UWK_PlayerTargetLockComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<AWK_PlayerCharacter>(GetOwner());
	if (Owner)
	{
		OwnerController = Cast<AWK_PlayerController>(Owner->GetController());
	}
}


void UWK_PlayerTargetLockComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CheckIsValid()) {CancelTargetLock(); return;}
	SetWidgetLocation();
	UpdateCameraRotation(DeltaTime);
	UpdatePlayerRotation(DeltaTime);
}

void UWK_PlayerTargetLockComponent::ActivateTargetLock()
{
	FindAvailableActors();
	if (AvailableActors.Num() == 0)
	{
		CancelTargetLock();
		return;
	}

	CurrentNearestTarget = FindNearestTargetInAvailableActors();
	if (CurrentNearestTarget == nullptr)
	{
		CancelTargetLock();
		return;
	}
	DrawTargetLockWidget();
	SetWidgetLocation();
	Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
	SetComponentTickEnabled(true);	
}

void UWK_PlayerTargetLockComponent::FindAvailableActors()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Owner);
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		Owner->GetActorLocation(),
		SphereSize,
		ObjectTypesToSearch,
		nullptr,
		ActorsToIgnore,
		 AvailableActors  
	);
}

AActor* UWK_PlayerTargetLockComponent::FindNearestTargetInAvailableActors()
{
	AActor* NearestActor = nullptr;
	while (AvailableActors.Num() > 0)
	{
		NearestActor = UGameplayStatics::FindNearestActor(Owner->GetActorLocation(), AvailableActors, DistanceToTarget);
		bool bIsEnemy = UWK_BlueprintFunctionLibrary::IsTargetHostile(Cast<APawn>(NearestActor), Owner);
		if (bIsEnemy) break;
		else
		{
			AvailableActors.Remove(NearestActor);
		}
	}
	if (DistanceToTarget > DetectDistance) return nullptr;
	if (NearestActor != nullptr)
	{
		return NearestActor;
	}
	return nullptr;
}

void UWK_PlayerTargetLockComponent::DrawTargetLockWidget()
{
	if (TargetLockWidget == nullptr)
	{
		check(TargetLockWidgetClass)
		TargetLockWidget = CreateWidget<UUserWidget>(OwnerController, TargetLockWidgetClass);
		check(TargetLockWidget);
	}

	TargetLockWidget->AddToViewport();
}

void UWK_PlayerTargetLockComponent::SetWidgetLocation()
{
	if (!CheckIsValid()) {CancelTargetLock(); return;}
	
	USkeletalMeshComponent* Mesh = CurrentNearestTarget->GetComponentByClass<USkeletalMeshComponent>();
	FVector TargetWorldLocation = Mesh->GetSocketLocation(FName("TargetLockSocket"));

	
	FVector2D ScreenPosition;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		OwnerController,
		TargetWorldLocation,
		ScreenPosition,
		true
		);

	if (WidgetSize == FVector2D::ZeroVector)
	{
		TargetLockWidget->WidgetTree->ForEachWidget([this](UWidget* WidgetFound)
	   {
		   if (USizeBox* SizeBox = Cast<USizeBox>(WidgetFound))
		   {
				WidgetSize.X = SizeBox->GetWidthOverride();
		   		WidgetSize.Y = SizeBox->GetHeightOverride();
		   }
	   });
	}

	ScreenPosition -= WidgetSize / 2.f;

	TargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UWK_PlayerTargetLockComponent::UpdateCameraRotation(float DeltaTime)
{
	if (!CheckIsValid()) {CancelTargetLock(); return;}
	USkeletalMeshComponent* Mesh = CurrentNearestTarget->GetComponentByClass<USkeletalMeshComponent>();
	FVector TargetLocation = Mesh->GetSocketLocation(FName("TargetLockSocket"));
	
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), TargetLocation);
	FRotator CurrentRotation = OwnerController->GetControlRotation();
			
	FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.0f);
	SmoothRotation.Pitch = FMath::Clamp(SmoothRotation.Pitch, -40.0f, 5.f);
	OwnerController->SetControlRotation(SmoothRotation);
}

void UWK_PlayerTargetLockComponent::UpdatePlayerRotation(float DeltaTime)
{
	if (!CheckIsValid()) {CancelTargetLock(); return;}

	UCharacterMovementComponent* MovementComponent = Owner->GetCharacterMovement();
	if (!MovementComponent) return;
	
	bool bIsSprinting = UWK_BlueprintFunctionLibrary::ActorHasTag(Owner, WKGameplayTags::Player_Status_Movement_Sprint);
	bool bIsDodge = UWK_BlueprintFunctionLibrary::ActorHasTag(Owner, WKGameplayTags::Player_Status_Dodge);
	bool bIsParry = UWK_BlueprintFunctionLibrary::ActorHasTag(Owner, WKGameplayTags::Player_Status_Parry);
	FVector InputVector = MovementComponent->GetLastInputVector();
	
	// if (bIsDodge) return;
	if (bIsParry || bIsSprinting || (InputVector.IsZero() && !bIsDodge))
	{
		Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
		return;
	}
	else
	{
		Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	FVector PlayerLoc = Owner->GetActorLocation();
	USkeletalMeshComponent* Mesh = CurrentNearestTarget->GetComponentByClass<USkeletalMeshComponent>();
	FVector TargetLoc = Mesh->GetSocketLocation(FName("TargetLockSocket"));

	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(PlayerLoc, TargetLoc);
	LookAtRot.Pitch = 0.0f;
	LookAtRot.Roll = 0.0f;
	
	FRotator CurrentRot = Owner->GetActorRotation();
	FRotator SmoothRot = FMath::RInterpConstantTo(CurrentRot, LookAtRot, DeltaTime, 250.f);
	
	Owner->SetActorRotation(SmoothRot);
}

void UWK_PlayerTargetLockComponent::Clean()
{
	AvailableActors.Empty();
	CurrentNearestTarget = nullptr;
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(GetOwner(),WKGameplayTags::Player_Status_TargetLock);
	if (TargetLockWidget != nullptr)
	{
		TargetLockWidget->RemoveFromParent();
	}
}

bool UWK_PlayerTargetLockComponent::CheckIsValid()
{
	if (!Owner) return false;
	if (CurrentNearestTarget == nullptr || TargetLockWidget == nullptr)
	{
		return false;
	}
	if (UWK_BlueprintFunctionLibrary::ActorHasTag(CurrentNearestTarget, WKGameplayTags::Shared_Status_Death))
	{
		return false;
	}
	return true;
}

void UWK_PlayerTargetLockComponent::CancelTargetLock()
{
	Clean();
	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
	SetComponentTickEnabled(false);
	TargetLockOnDelegate.Broadcast(false);
}

