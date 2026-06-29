// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WK_PlayerCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "WK_BlueprintFunctionLibrary.h"
#include "WK_GameplayTags.h"
#include "AbilitySystem/WK_AbilitySystemComponent.h"
#include "Character/Component/Combat/WK_PlayerCombatComponent.h"
#include "Character/Component/Combat/Combo/WK_PlayerComboComponent.h"
#include "Character/Component/Combat/TargetLock/WK_PlayerTargetLockComponent.h"
#include "Character/Component/UI/WK_PlayerUIComponent.h"
#include "Components/CapsuleComponent.h"
#include "Data/WK_InputDataConfig.h"
#include "Data/WK_PlayerStartUpAbilities.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/WK_EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Wukong/WK_DebugHelper.h"


AWK_PlayerCharacter::AWK_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	FootSceneComponent = CreateDefaultSubobject<USceneComponent>("FootSceneComponent");
	FootSceneComponent->SetupAttachment(GetRootComponent());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	PlayerComboComponent = CreateDefaultSubobject<UWK_PlayerComboComponent>("PlayerComboComponent");
	PlayerTargetLockComponent = CreateDefaultSubobject<UWK_PlayerTargetLockComponent>("PlayerTargetLockComponent");
	PlayerUIComponent = CreateDefaultSubobject<UWK_PlayerUIComponent>("PlayerUIComponent");
	PlayerCombatComponent = CreateDefaultSubobject<UWK_PlayerCombatComponent>("PlayerCombatComponent");
	
	WeaponCollisionBox = CreateDefaultSubobject<UCapsuleComponent>("WeaponCollisionCapsule");
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);

}

void AWK_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	UWK_BlueprintFunctionLibrary::AddGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Run);
	if (WeaponAttachSocketName.IsValid())
	{
		WeaponCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
	}

	
}

void AWK_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UWK_PlayerStartUpAbilities* LoadedAbilities = PlayerStartAbilityData.LoadSynchronous();
	if (LoadedAbilities)
	{
		LoadedAbilities->GrantAbilityToActorASC(GetWKAbilitySystemComponent(), 1);
	}
}

void AWK_PlayerCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UWK_BlueprintFunctionLibrary::IsTargetHostile(this, Cast<APawn>(OtherActor)))
	{
		GetPawnCombatComponent()->WeaponHitBegin(OtherActor);
	}
}



void AWK_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFollowPelvis)
	{
		float PelvisHeight = GetMesh()->GetSocketLocation(FName("pelvis")).Z;
		float CharacterHeight = GetActorLocation().Z;

		float JumpHeight = PelvisHeight - CharacterHeight;
		SpringArmComponent->TargetOffset.Z = FMath::FInterpTo(SpringArmComponent->TargetOffset.Z, JumpHeight, DeltaTime, 10.f);
	}
	else
	{
		SpringArmComponent->TargetOffset.Z = FMath::FInterpTo(SpringArmComponent->TargetOffset.Z, 0, DeltaTime, 10.f);
	}


}

void AWK_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	Subsystem->AddMappingContext(InputDataConfig->DefaultMappingContext, 0);

	UWK_EnhancedInputComponent* EnhancedInput = Cast<UWK_EnhancedInputComponent>(PlayerInputComponent);
	EnhancedInput->BindMoveInputAction(InputDataConfig, WKGameplayTags::Player_Input_Move,ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	EnhancedInput->BindMoveInputAction(InputDataConfig, WKGameplayTags::Player_Input_Look,ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	// EnhancedInput->BindMoveInputAction(InputDataConfig, WKGameplayTags::Player_Input_Jump,ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);
	EnhancedInput->BindMoveInputAction(InputDataConfig, WKGameplayTags::Player_Input_Movement_Sprint,this, &ThisClass::Input_Sprint_Start, &ThisClass::Input_Sprint_Stop);
	EnhancedInput->BindMoveInputAction(InputDataConfig, WKGameplayTags::Player_Input_Movement_Walk,this, &ThisClass::Input_Walk_Start, &ThisClass::Input_Walk_Stop);

	EnhancedInput->BindAbilityInputAction(InputDataConfig, this, &ThisClass::OnInputPressed, &ThisClass::OnInputReleased);
}

UWK_PawnUIComponent* AWK_PlayerCharacter::GetPawnUIComponent() const
{
	return GetPlayerUIComponent();
}

UWK_PawnCombatComponent* AWK_PlayerCharacter::GetPawnCombatComponent() 
{
	return GetPlayerCombatComponent();
}


void AWK_PlayerCharacter::BP_StopSprint()
{
	Input_Sprint_Stop();
}

AActor* AWK_PlayerCharacter::GetTargetActor() const
{
	if (PlayerTargetLockComponent != nullptr)
	{
		return PlayerTargetLockComponent->GetCurrentNearestTarget();
	}
	return nullptr;
}


void AWK_PlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	if (IsValid(GetController()))
	{
		
		FRotator YawRotation = FRotator(0,GetControlRotation().Yaw, 0);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		if (UWK_BlueprintFunctionLibrary::ActorHasTag(this, WKGameplayTags::Player_Status_TargetLock))
		{
			AActor* TargetActor = PlayerTargetLockComponent->GetCurrentNearestTarget();
			// 플레이어가 'W(앞)'만 누르고 있고, 적과 너무 가까우면
			if (TargetActor != nullptr && MovementVector.Y > 0.0f)
			{
				float Distance = GetDistanceTo(TargetActor);
				float OrbitRadius = UWK_BlueprintFunctionLibrary::GetEnemyAcceptRadius(TargetActor);

				if (Distance < OrbitRadius)
				{
					// A. 타겟 방향 구하기
					FVector DirToTarget = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
					DirToTarget.Z = 0.f;
					DirToTarget.Normalize();
					
					// B. 원 운동 방향(접선) 구하기 (타겟을 중심으로 90도 꺾은 방향)
					FVector OrbitLeft = FVector::CrossProduct(DirToTarget, FVector::UpVector); // 기본 왼쪽
					FVector OrbitRight = -OrbitLeft;
					
					// C. 내가 지금 타겟의 오른쪽인지 왼쪽인지 판단
					// (내 카메라 앞방향과 왼쪽 접선이 같은 방향이면 왼쪽으로 도는 게 맞음)
					FVector OrbitDir = (FVector::DotProduct(ForwardDirection, OrbitLeft) > FVector::DotProduct(ForwardDirection, OrbitRight) 
						? OrbitLeft : OrbitRight);
					
					// 거리 비율에 따라  섞기
					// 거리가 300이면 Alpha=0 (직진), 거리가 150이면 Alpha=1 (완전 원운동)
					float Alpha = FMath::Clamp((OrbitRadius - Distance) / 150.0f, 0.0f, 1.0f);

					// 앞 방향을 원운동 방향으로 부드럽게 틂
					ForwardDirection = FMath::Lerp(ForwardDirection, OrbitDir, Alpha).GetSafeNormal();
				}
			}
		}
		
		AddMovementInput(RightDirection, MovementVector.X);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		
		if (MovementVector.IsNearlyZero()) return;
		
		FVector InputWorldDir = (ForwardDirection * MovementVector.Y) + (RightDirection * MovementVector.X);
		InputWorldDir.Normalize();

		//차이 계산
		FRotator TargetRot = InputWorldDir.Rotation();
		FRotator CurrentRot = GetActorForwardVector().Rotation();

		
		
		
		float DeltaYaw = UKismetMathLibrary::NormalizedDeltaRotator(TargetRot, CurrentRot).Yaw;
		
		if (FMath::Abs(DeltaYaw) >= 70.f)
		{
			if (!UWK_BlueprintFunctionLibrary::ActorHasTag(this, WKGameplayTags::Player_Status_Turn))
			{
				FGameplayEventData Payload;
    
				
				Payload.EventMagnitude = DeltaYaw; 
				Payload.Instigator = this;
				Payload.Target = this;
				
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
					this, 
					WKGameplayTags::Event_Player_Turn, 
					Payload
				);
			}
		}
	}

	
}

void AWK_PlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookVector = InputActionValue.Get<FVector2D>();

	if (IsValid(GetController()))
	{
		AddControllerPitchInput(LookVector.Y);
		AddControllerYawInput(LookVector.X);
	}
}

// void AWK_PlayerCharacter::Input_Jump(const FInputActionValue& InputActionValue)
// {
// 	if(GetCharacterMovement()->IsFalling()) return;
// 	if (UWK_BlueprintFunctionLibrary::ActorHasTag(this, WKGameplayTags::Player_Status_Attack_Light) || 
// 	UWK_BlueprintFunctionLibrary::ActorHasTag(this, WKGameplayTags::Player_Status_Dodge)) return;
// 	GetCharacterMovement()->DoJump(true);
// }

void AWK_PlayerCharacter::Input_Sprint_Start()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Run);
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Walk);
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Sprint);
	
	UWK_BlueprintFunctionLibrary::AddGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Sprint);
}

void AWK_PlayerCharacter::Input_Sprint_Stop()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Sprint);
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Run);

	UWK_BlueprintFunctionLibrary::AddGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Run);
}

void AWK_PlayerCharacter::Input_Walk_Start()
{
	if (UWK_BlueprintFunctionLibrary::ActorHasTag(this, WKGameplayTags::Player_Status_Movement_Sprint)) return;
	
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Walk);
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Run);
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Sprint);
	
	UWK_BlueprintFunctionLibrary::AddGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Walk);
}


void AWK_PlayerCharacter::Input_Walk_Stop()
{
	if (UWK_BlueprintFunctionLibrary::ActorHasTag(this, WKGameplayTags::Player_Status_Movement_Sprint)) return;
	
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Walk);
	UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Run);

	UWK_BlueprintFunctionLibrary::AddGameplayTagToActor(this, WKGameplayTags::Player_Status_Movement_Run);
}

void AWK_PlayerCharacter::OnInputPressed(FGameplayTag InputTag)
{
	WKAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void AWK_PlayerCharacter::OnInputReleased(FGameplayTag InputTag)
{
	WKAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}

void AWK_PlayerCharacter::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, WeaponAttachSocketName))
	{
		WeaponCollisionBox->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,WeaponAttachSocketName);
		
	}
}

