// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/WK_PlayerSummonMonkeyAbility.h"

#include "Character/WK_PlayerCharacter.h"

TArray<FVector> UWK_PlayerSummonMonkeyAbility::GetSpawnLocations()
{
	const FVector PlayerForward =  GetPlayerCharacterFromActorInfo()->GetActorForwardVector();
	const FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	const FRotator PlayerRotation = GetPlayerCharacterFromActorInfo()->GetActorRotation();

	FVector LeftSpread =PlayerForward.RotateAngleAxis(SummonSpread / 2.f, FVector::UpVector);
	float DeltaSpread = SummonSpread / SummonCount;
	TArray<FVector> SummonLocations;
	int32 Index = 1;
	while (SummonLocations.Num() < SummonCount)
	{
		FVector SummonDir = LeftSpread.RotateAngleAxis(-DeltaSpread * Index, FVector::UpVector);\
		float SummonDistance = FMath::RandRange(SummonMinDistance, SummonMaxDistance);
		FVector SummonLocation = PlayerLocation + SummonDir * SummonDistance;

		FHitResult SummonHitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(SummonHitResult, SummonLocation + FVector(0,0, 400.f),
				SummonLocation + FVector(0,0, -400.f), ECC_Visibility);

		if (bHit)
		{
			SummonLocation = SummonHitResult.ImpactPoint;
		}

		SummonLocation.Z += 50.f;
		SummonLocations.Add(SummonLocation);
		Index++;
	}

	return SummonLocations;
}
