


#include "Character/WK_BaseCharacter.h"
#include "MotionWarpingComponent.h"
#include "AbilitySystem/WK_AbilitySystemComponent.h"
#include "AbilitySystem/WK_AttributeSet.h"

AWK_BaseCharacter::AWK_BaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WKAbilitySystemComponent = CreateDefaultSubobject<UWK_AbilitySystemComponent>("WKAbilitySystemComponent");
	WKAttributeSet = CreateDefaultSubobject<UWK_AttributeSet>("WKAttributeSet");
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
}

// Called when the game starts or when spawned
void AWK_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWK_BaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (WKAbilitySystemComponent != nullptr)
	{
		WKAbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
}

void AWK_BaseCharacter::SetAnimRootMotionScaleInBP(float NewScale)
{
	SetAnimRootMotionTranslationScale(NewScale);
}

UWK_PawnUIComponent* AWK_BaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

UWK_PawnCombatComponent* AWK_BaseCharacter::GetPawnCombatComponent()
{
	return nullptr;
}


