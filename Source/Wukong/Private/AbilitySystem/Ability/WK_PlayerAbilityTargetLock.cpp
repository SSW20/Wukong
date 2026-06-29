// // Fill out your copyright notice in the Description page of Project Settings.
//
//
// #include "AbilitySystem/Ability/WK_PlayerAbilityTargetLock.h"
//
// #include "Blueprint/UserWidget.h"
// #include "Blueprint/WidgetLayoutLibrary.h"
// #include "Blueprint/WidgetTree.h"
// #include "Character/WK_PlayerCharacter.h"
// #include "Components/SizeBox.h"
// #include "GameFramework/CharacterMovementComponent.h"
// #include "Kismet/GameplayStatics.h"
// #include "Kismet/KismetMathLibrary.h"
//
// class USizeBox;
//
// void UWK_PlayerAbilityTargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
//                                                   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
//                                                   const FGameplayEventData* TriggerEventData)
// {
// 	TryLockOnTarget();
// 	GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->bOrientRotationToMovement = false;
// 	GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->bUseControllerDesiredRotation = true;
// 	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
// }
//
// void UWK_PlayerAbilityTargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
// 	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
// 	bool bReplicateEndAbility, bool bWasCancelled)
// {
// 	CleanUp();
// 	GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->bOrientRotationToMovement = true;
// 	GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->bUseControllerDesiredRotation = false;
// 	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
// }
//
// void UWK_PlayerAbilityTargetLock::UpdateWidgetPosition(float DeltaTime)
// {
// 	// 죽었을 때의 상태 태그 추가 후 OR
// 	if (CurrentNearestTarget == nullptr)
// 	{
// 		CancelTargetLockAbility();
// 		return;
// 	}
// 	else 
// 	{
// 		SetWidgetLocation();
//
// 		FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
// 		USkeletalMeshComponent* Mesh = CurrentNearestTarget->GetComponentByClass<USkeletalMeshComponent>();
// 		FVector TargetLocation = Mesh->GetSocketLocation(FName("TargetLockSocket"));
// 		
// 		// 나중에 바꾸셈
// 		AController* Controller = CurrentActorInfo->PlayerController.Get();
// 		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetLocation);
// 		FRotator CurrentRotation = Controller->GetControlRotation();
// 		
// 		FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 5.0f);
// 		SmoothRotation.Pitch = FMath::Clamp(SmoothRotation.Pitch, -40.0f, 5.f);
// 		Controller->SetControlRotation(SmoothRotation);
// 	}
// }
//
// void UWK_PlayerAbilityTargetLock::TryLockOnTarget()
// {
// 	FindAvailableActors();
// 	if (AvailableActors.Num() == 0)
// 	{
// 		CancelTargetLockAbility();
// 	}
//
// 	CurrentNearestTarget = FindNearestTargetInAvailableActors();
// 	if (CurrentNearestTarget == nullptr)
// 	{
// 		CancelTargetLockAbility();
// 	}
// 	DrawTargetLockWidget();
// 	SetWidgetLocation();
// }
//
// void UWK_PlayerAbilityTargetLock::CleanUp()
// {
// 	AvailableActors.Empty();
// 	CurrentNearestTarget = nullptr;
// 	GetPlayerCharacterFromActorInfo()->SetTargetActor(nullptr);
// 	TargetLockWidget->RemoveFromParent();
// }
//
// void UWK_PlayerAbilityTargetLock::FindAvailableActors()
// {
// 	TArray<AActor*> ActorsToIgnore;ActorsToIgnore.Add(GetPlayerCharacterFromActorInfo());
// 	UKismetSystemLibrary::SphereOverlapActors(
// 		GetWorld(),
// 		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
// 		SphereSize,
// 		ObjectTypesToSearch,
// 		nullptr,
// 		ActorsToIgnore,
// 		 AvailableActors  
// 	);
// }
//
// AActor* UWK_PlayerAbilityTargetLock::FindNearestTargetInAvailableActors()
// {
// 	AActor* NearestActor = UGameplayStatics::FindNearestActor(GetPlayerCharacterFromActorInfo()->GetActorLocation(), AvailableActors, DistanceToTarget);
// 	if (NearestActor != nullptr)
// 	{
// 		GetPlayerCharacterFromActorInfo()->SetTargetActor(NearestActor);
// 		return NearestActor;
// 	}
// 	GetPlayerCharacterFromActorInfo()->SetTargetActor(nullptr);
// 	return nullptr;
// }
//
// void UWK_PlayerAbilityTargetLock::DrawTargetLockWidget()
// {
// 	if (TargetLockWidget == nullptr)
// 	{
// 		check(TargetLockWidgetClass)
// 		TargetLockWidget = CreateWidget<UUserWidget>(CurrentActorInfo->PlayerController->GetWorld(), TargetLockWidgetClass);
// 		check(TargetLockWidget);
// 	}
//
// 	TargetLockWidget->AddToViewport();
// }
//
// void UWK_PlayerAbilityTargetLock::SetWidgetLocation()
// {
// 	if (CurrentNearestTarget == nullptr || TargetLockWidget == nullptr)
// 	{
// 		CancelTargetLockAbility();
// 		return;
// 	}
//
// 	
// 	USkeletalMeshComponent* Mesh = CurrentNearestTarget->GetComponentByClass<USkeletalMeshComponent>();
// 	FVector TargetWorldLocation = Mesh->GetSocketLocation(FName("TargetLockSocket"));
//
// 	
// 	FVector2D ScreenPosition;
// 	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
// 		CurrentActorInfo->PlayerController.Get(),
// 		TargetWorldLocation,
// 		ScreenPosition,
// 		true
// 		);
//
// 	if (WidgetSize == FVector2D::ZeroVector)
// 	{
// 		TargetLockWidget->WidgetTree->ForEachWidget([this](UWidget* WidgetFound)
// 	   {
// 		   if (USizeBox* SizeBox = Cast<USizeBox>(WidgetFound))
// 		   {
// 				WidgetSize.X = SizeBox->GetWidthOverride();
// 		   		WidgetSize.Y = SizeBox->GetHeightOverride();
// 		   }
// 	   });
// 	}
//
// 	ScreenPosition -= WidgetSize / 2.f;
//
// 	TargetLockWidget->SetPositionInViewport(ScreenPosition, false);
// }
//
// void UWK_PlayerAbilityTargetLock::CancelTargetLockAbility()
// {
// 	CancelAbility(GetCurrentAbilitySpecHandle(),GetCurrentActorInfo(),GetCurrentActivationInfo(),true);
// }
