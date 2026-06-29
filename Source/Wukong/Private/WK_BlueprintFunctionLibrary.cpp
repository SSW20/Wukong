

#include "WK_BlueprintFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystem/WK_AbilitySystemComponent.h"
#include "Actions/WK_CoolDownTimer.h"
#include "Character/WK_EnemyCharacter.h"
#include "Character/WK_PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Interface/WK_PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Types/WK_EnumTypes.h"
#include "Wukong/WK_DebugHelper.h"


// AddLooseGameplayTag -->	서버에서는 자동 Rep 안되니 조심

class FWK_CoolDownTimer;

void UWK_BlueprintFunctionLibrary::AddGameplayTagToActor(AActor* Actor, const FGameplayTag& Tag)
{
	if (!IsValid(Actor))
	{
		return;
	}
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
	if (!ASC)
	{
		return;
	}
	if (ASC->HasMatchingGameplayTag(Tag)) return;
	ASC->AddLooseGameplayTag(Tag);
}

void UWK_BlueprintFunctionLibrary::RemoveGameplayTagToActor(AActor* Actor, const FGameplayTag& Tag)
{
	if (!IsValid(Actor))
	{
		return;
	}

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
	if (!ASC)
	{
		return;
	}
	ASC->RemoveLooseGameplayTag(Tag);
}

bool UWK_BlueprintFunctionLibrary::ActorHasTag(AActor* Actor, const FGameplayTag& Tag)
{
	if (!IsValid(Actor))
	{
		return false;
	}
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
	if (!ASC)
	{
		return false;
	}
	return ASC->HasMatchingGameplayTag(Tag);
}

int UWK_BlueprintFunctionLibrary::FindAngleIndex(const float& Angle)
{
	if (-160 > Angle && Angle >= -180.f) return 0;
	if (-70 > Angle && Angle > -100.f) return 1;
	if ( 70<Angle && Angle <= 100.f) return 2;
	if ( 160<Angle && Angle <= 180.f) return 3;
	return 5;
}

EActorDirection UWK_BlueprintFunctionLibrary::CalculateActorDirection(ACharacter* Character, FVector& Direction, bool bToggle)
{
	
	if (Character != nullptr)
	{
		Direction = Character->GetMovementComponent()->GetLastInputVector();
		Direction.Normalize();
		if (Direction.IsZero())
		{
			Direction = Character->GetActorForwardVector();
			return EActorDirection::Forward;
		}
		if (!bToggle) return EActorDirection::Forward;		
			
		FRotator ActorRotation = Character->GetActorRotation();
    
		// 캐릭터 기준에서의 입력 방향 
		FVector LocalInputVector = ActorRotation.UnrotateVector(Direction);
		if (FMath::Abs(LocalInputVector.X) > FMath::Abs(LocalInputVector.Y))
		{
			if (LocalInputVector.X > 0.f)
			{
				return EActorDirection::Forward;
			}
			return EActorDirection::Back;
		}
		if (LocalInputVector.Y > 0.f)
		{
			return EActorDirection::Right;
		}
		else
		{
			return EActorDirection::Left;
		}
	}
	return EActorDirection::Forward;
}

int32 UWK_BlueprintFunctionLibrary::CalculateHitReactDirection(AActor* Attacker, AActor* TargetActor)
{
	FVector AttackerLocation = Attacker->GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();
	
	FVector DirToAttacker = (AttackerLocation - TargetLocation).GetSafeNormal();
	FVector TargetForwardVector = TargetActor->GetActorForwardVector();
	
	// 앞 뒤 판별
	float DotForward =  FVector::DotProduct(DirToAttacker, TargetForwardVector);
	
	// 좌우 판별
	FVector TargetRightVector = TargetActor->GetActorRightVector();
	float DotRight = FVector::DotProduct(DirToAttacker, TargetRightVector);

	if (AWK_PlayerCharacter* Player = Cast<AWK_PlayerCharacter>(TargetActor))
	{
		return DotForward > 0.f ? 0 : 1;
	}
	
	// 0 : 앞, 1 : 뒤, 2: 오, 3: 왼
	if (FMath::Abs(DotForward) > FMath::Abs(DotRight))
	{
		return DotForward > 0.f ? 0 : 1;
	}
	else
	{
		// 애니메이션 부족으로 인해 옆은 앞으로 판정
		return DotRight > 0.f ? 2 : 3;
	}
}

FRotator UWK_BlueprintFunctionLibrary::CalculateActorRotation(AActor* Attacker, AActor* TargetActor)
{
	if (!IsValid(Attacker)) return FRotator();
	if (!IsValid(TargetActor)) return Attacker->GetActorRotation();

	return UKismetMathLibrary::FindLookAtRotation(Attacker->GetActorLocation(), TargetActor->GetActorLocation());
}

UWK_PawnCombatComponent* UWK_BlueprintFunctionLibrary::NativeGetPawnCombatComponent(AActor* Actor)
{
	if (!IsValid(Actor)) return nullptr;
	
	if (Actor->Implements<UWK_PawnCombatInterface>())
	{
		IWK_PawnCombatInterface* CombatInterface = Cast<IWK_PawnCombatInterface>(Actor);
		return CombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UWK_PawnCombatComponent* UWK_BlueprintFunctionLibrary::BP_GetPawnCombatComponent(AActor* Actor)
{
	return NativeGetPawnCombatComponent(Actor);
}

EDistanceToTarget UWK_BlueprintFunctionLibrary::GetDistanceToTarget(float Distance, float TooFar, float Far,
	float Middle, float Close)
{
	if (Distance > TooFar)
		return EDistanceToTarget::TooFar;

	if (Distance > Far)
		return EDistanceToTarget::Far;

	if (Distance > Middle)
		return EDistanceToTarget::Middle;

	if (Distance > Close)
		return EDistanceToTarget::Close;

	return EDistanceToTarget::TooClose;

	// if (Distance > 2500.f)
	// 	return EDistanceToTarget::TooFar;
	//
	// if (Distance > 1800.f)
	// 	return EDistanceToTarget::Far;
	//
	// if (Distance > 1000.f)
	// 	return EDistanceToTarget::Middle;
	//
	// if (Distance > 600.f)
	// 	return EDistanceToTarget::Close;
	//
	// return EDistanceToTarget::TooClose;
}

FGameplayTag UWK_BlueprintFunctionLibrary::GetTagByName(FName TagName)
{
	return UGameplayTagsManager::Get().RequestGameplayTag(TagName);
}

bool UWK_BlueprintFunctionLibrary::IsTargetHostile(APawn* OwningPawn, APawn* TargetPawn)
{
	if (OwningPawn == nullptr || TargetPawn == nullptr) return false;
	IGenericTeamAgentInterface* OwningTeamAgent = Cast<IGenericTeamAgentInterface>(OwningPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (OwningTeamAgent && TargetTeamAgent)
	{
		return OwningTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

void UWK_BlueprintFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
	float& OutRemainingTime, ECountDownActionInput CountDownInput, ECountDownActionOutput& CountDownOutput,
	FLatentActionInfo LatentInfo, bool bReverse)
{
	UWorld* World = nullptr;
	if (GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject,EGetWorldErrorMode::LogAndReturnNull);
	}

	if (!World)
	{
		return;
	}

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	FWK_CoolDownTimer* FoundAction = LatentActionManager.FindExistingAction<FWK_CoolDownTimer>(LatentInfo.CallbackTarget, LatentInfo.UUID);

	if (CountDownInput == ECountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FWK_CoolDownTimer(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo, bReverse));
		}
	}

	if (CountDownInput == ECountDownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}

float UWK_BlueprintFunctionLibrary::GetEnemyAcceptRadius(AActor* Enemy)
{
	AWK_EnemyCharacter* EnemyCharacter = Cast<AWK_EnemyCharacter>(Enemy);
	if (EnemyCharacter == nullptr) return 0.f;

	return EnemyCharacter->GetAcceptRadius();
	
}

TArray<FVector> UWK_BlueprintFunctionLibrary::GetRandomPointInRadius(const FVector& CenterLocation,const FVector& Forward,
	int32 PointCount,float DistanceToCenter)
{
	TArray<FVector> Points;
	const float DeltaAngle = 360 / PointCount;

	const FVector RightVector = FVector::CrossProduct(FVector::UpVector, Forward).GetSafeNormal();
	if (PointCount > 1)
	{
		for (int i = 0; i < PointCount; i++)
		{
			float Angle = DeltaAngle * i;
			float Radian = FMath::DegreesToRadians(Angle);
			FVector Direction = Forward * FMath::Cos(Radian) + RightVector * FMath::Sin(Radian);
			FVector Point = CenterLocation + Direction * DistanceToCenter;
			Points.Add(Point);
		}
	}
	return Points;
}

TArray<FVector> UWK_BlueprintFunctionLibrary::GetRandomPointInLine(const FVector& CenterLocation,const FVector& Forward, const FVector& Direction, int32 PointCount,
	float DistanceByPoints)
{
	TArray<FVector> Points;
	for (int32 i= 0; i < PointCount; i++)
	{
		FVector PointLoc = CenterLocation + (DistanceByPoints * Direction * i);
		Points.Add(PointLoc);
	}

	return Points;
}

FActiveGameplayEffectHandle UWK_BlueprintFunctionLibrary::NativeApplyEffectToTarget(AActor* TargetActor,
                                                                                    const FGameplayEffectSpecHandle& SpecHandle)
{
	UWK_AbilitySystemComponent* TargetASC = Cast<UWK_AbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
	if (TargetASC)
	{
		return TargetASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, TargetASC);
	}
	return FActiveGameplayEffectHandle();
}

FActiveGameplayEffectHandle UWK_BlueprintFunctionLibrary::BP_ApplyEffectToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& SpecHandle)
{
	return NativeApplyEffectToTarget(TargetActor, SpecHandle);
}