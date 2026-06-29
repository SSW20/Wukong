// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WK_PlayerCloneCharacter.h"

#include "WK_BlueprintFunctionLibrary.h"
#include "Character/Component/Combat/WK_PlayerCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Data/WK_StartUpAbilities.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AWK_PlayerCloneCharacter::AWK_PlayerCloneCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0, 180.f, 0);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	PlayerCombatComponent = CreateDefaultSubobject<UWK_PlayerCombatComponent>("PlayerCombatComponent");
	
	WeaponCollisionBox = CreateDefaultSubobject<UCapsuleComponent>("WeaponCollisionCapsule");
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnComponentBeginOverlap);
}

// Called when the game starts or when spawned
void AWK_PlayerCloneCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!WKAbilitySystemComponent) return;
	if (PlayerCloneStartAbilityData.IsNull()) return;

	UWK_StartUpAbilities* Data = PlayerCloneStartAbilityData.LoadSynchronous();
	if (!Data) return;

	Data->GrantAbilityToActorASC(WKAbilitySystemComponent, 1);
	
	if (WeaponAttachSocketName.IsValid())
	{
		WeaponCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachSocketName);
	}
}
void AWK_PlayerCloneCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AWK_PlayerCloneCharacter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (UWK_BlueprintFunctionLibrary::IsTargetHostile(this, Cast<APawn>(OtherActor)))
	{
		GetPawnCombatComponent()->WeaponHitBegin(OtherActor);
	}
}


// Called every frame
void AWK_PlayerCloneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWK_PlayerCloneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UWK_PawnCombatComponent* AWK_PlayerCloneCharacter::GetPawnCombatComponent()
{
	return PlayerCombatComponent;
}

