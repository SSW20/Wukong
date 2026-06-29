// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "WK_ProjectileBase.generated.h"

class UGameplayEffect;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class WUKONG_API AWK_ProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWK_ProjectileBase();
	
	virtual bool IsValidOverlap(AActor* OtherActor);

	void InitDamage(float InDamage, TSubclassOf<UGameplayEffect> InDamageClass)
	{
		Damage = InDamage;
		DamageEffectClass = InDamageClass;
	}
	void SetHomingTarget(AActor* InTarget) {HomingTarget = InTarget;}
	void SetHoming(bool Homing) {bHoming = Homing;}
	void SetGround(bool Ground) {bGround = Ground;}

	void TickHomingGround(float DeltaTime);
	void TickHomingTarget(float DeltaTime);
	void TickGround(float DeltaTime);
	void TickProjectileMovement(float DeltaTime);
protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UFUNCTION(BlueprintCallable)
	void OnHit();
	virtual void Destroyed() override;


	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 10.f;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY()
	float Damage = 0.f;

	UPROPERTY()
	AActor* HomingTarget;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	UNiagaraSystem* HitNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* ElectricSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* HitSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	UAudioComponent* AudioComp;
	
	UPROPERTY(EditDefaultsOnly, Category="GroundHoming")
	float MoveSpeed = 1600.f;

	UPROPERTY(EditDefaultsOnly, Category="GroundHoming")
	float TurnSpeedDegPerSec = 720.f; 

	UPROPERTY(EditDefaultsOnly, Category="GroundHoming")
	float TraceUp = 60.f;

	UPROPERTY(EditDefaultsOnly, Category="GroundHoming")
	float TraceDown = 300.f;

	UPROPERTY(EditDefaultsOnly, Category="GroundHoming")
	float GroundOffset = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category="GroundHoming")
	float GroundHeightThreshold = 20.f; 

	UPROPERTY(EditDefaultsOnly, Category="GroundHoming")
	TEnumAsByte<ECollisionChannel> GroundTraceChannel = ECC_WorldStatic;
	
	UPROPERTY()
	FVector CurrentMoveDir = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category="GroundHoming|Behind")
	float BehindDotThreshold = -0.2f;  

	UPROPERTY(EditDefaultsOnly, Category="GroundHoming|Behind")
	float BehindDestroyDelay = 1.2f;   

	UPROPERTY()
	float BehindTimeAccum = 0.f;

	UPROPERTY()
	bool bGround = true;

	UPROPERTY()
	bool bHoming = true;
private:
	FVector CalculateDesiredMoveDir() const;
	bool SnapToGround(const FVector& InCandidate, FVector& OutSnapped, FHitResult& OutHit) const;

	
};
