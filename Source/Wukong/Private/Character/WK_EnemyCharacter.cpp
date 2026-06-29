// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WK_EnemyCharacter.h"

#include "NiagaraFunctionLibrary.h"
#include "WK_BlueprintFunctionLibrary.h"
#include "WK_GameplayTags.h"
#include "Character/Component/Combat/WK_EnemyCombatComponent.h"
#include "Character/Component/UI/WK_EnemyUIComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Data/WK_EnemyStartUpAbilities.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Wukong/WK_DebugHelper.h"


// Sets default values
AWK_EnemyCharacter::AWK_EnemyCharacter()
{
	// 아니면 타이밍 이슈로 BB 바인드 되기전에 Perception 호출됨
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 360.f, 0);
	GetCharacterMovement()->MaxWalkSpeed = EnemyMaxWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UWK_EnemyCombatComponent>("EnemyCombatComponent");
	EnemyUIComponent = CreateDefaultSubobject<UWK_EnemyUIComponent>("EnemyUIComponent");
	// EnemyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyWidgetComponent");

	LeftHandCollisionBox = CreateDefaultSubobject<UCapsuleComponent>("LeftHandCollisionBox");
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	RightHandCollisionBox = CreateDefaultSubobject<UCapsuleComponent>("RightHandCollisionBox");
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LeftFootCollisionBox = CreateDefaultSubobject<UCapsuleComponent>("LeftFootCollisionBox");
	LeftFootCollisionBox->SetupAttachment(GetMesh());
	LeftFootCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	RightFootCollisionBox = CreateDefaultSubobject<UCapsuleComponent>("RightFootCollisionBox");
	RightFootCollisionBox->SetupAttachment(GetMesh());
	RightFootCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 나중에 표기 
	// EnemyWidgetComponent->SetupAttachment(GetMesh());

	OSTAudioComp = CreateDefaultSubobject<UAudioComponent>("OSTComp");
	LeftWeaponAudioComp = CreateDefaultSubobject<UAudioComponent>("LeftWeaponAudioComp");
	RightWeaponAudioComp = CreateDefaultSubobject<UAudioComponent>("RightWeaponAudioComp");

	OSTAudioComp->SetupAttachment(RootComponent);
	LeftWeaponAudioComp->SetupAttachment(LeftHandCollisionBox);
	RightWeaponAudioComp->SetupAttachment(RightHandCollisionBox);

	
}

void AWK_EnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
}

void AWK_EnemyCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (this != OtherActor)
	{
		GetEnemyCombatComponent()->WeaponHitBegin(OtherActor);
	}
}

// Called when the game starts or when spawned
void AWK_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (!WKAbilitySystemComponent) return;
	if (EnemyStartAbilityData.IsNull()) return;

	UWK_EnemyStartUpAbilities* Data = EnemyStartAbilityData.LoadSynchronous();
	if (!Data) return;

	Data->GrantAbilityToActorASC(WKAbilitySystemComponent, 1);

	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);

	LeftFootCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);
	RightFootCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);
	
	OSTAudioComp->SetSound(OST);
	LeftWeaponAudioComp->SetSound(LeftWeaponSound);
	RightWeaponAudioComp->SetSound(RightWeaponSound);
	
	OSTAudioComp->Play();
	LeftWeaponAudioComp->Play();
	RightWeaponAudioComp->Play();
}

// Called every frame
void AWK_EnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWK_EnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UWK_PawnCombatComponent* AWK_EnemyCharacter::GetPawnCombatComponent()
{
	return GetEnemyCombatComponent();
}

UWK_PawnUIComponent* AWK_EnemyCharacter::GetPawnUIComponent() const
{
	return GetEnemyUIComponent();
}

void AWK_EnemyCharacter::ClearSound()
{
	OSTAudioComp->Stop();
	LeftWeaponAudioComp->Stop();
	RightWeaponAudioComp->Stop();
}

void AWK_EnemyCharacter::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandAttachSocketName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,LeftHandAttachSocketName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandAttachSocketName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,RightHandAttachSocketName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightFootAttachSocketName))
	{
		RightFootCollisionBox->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,RightFootAttachSocketName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftFootAttachSocketName))
	{
		LeftFootCollisionBox->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,LeftFootAttachSocketName);
	}
}

