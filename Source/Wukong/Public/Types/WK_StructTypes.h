#pragma once

#include "WK_EnumTypes.h"
#include "WK_StructTypes.generated.h"

class UGameplayAbility;
USTRUCT(BlueprintType)
struct FActorDodgeAbility
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EActorDirection Direction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> Ability;
};

USTRUCT()
struct FWeaponCollisionCachedData
{
	GENERATED_BODY()
	float Radius = 0.f;
	float HalfHeight = 0.f;
	FVector RelLoc = FVector::ZeroVector;
	FRotator RelRot = FRotator::ZeroRotator;
};