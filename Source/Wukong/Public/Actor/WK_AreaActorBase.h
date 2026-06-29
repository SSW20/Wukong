// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "NiagaraSystem.h"
#include "WK_AreaActorBase.generated.h"

class UGameplayEffect;
class USphereComponent;

UCLASS()
class WUKONG_API AWK_AreaActorBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWK_AreaActorBase();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	void InitDamage(float InDamage, TSubclassOf<UGameplayEffect> InDamageClass)
	{
		Damage = InDamage;
		DamageEffectClass = InDamageClass;
	}
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	UPROPERTY(EditAnywhere, Category="Shockwave")
	float LifeSpan = 10.f;
	
	UPROPERTY(EditAnywhere, Category="Shockwave")
	float RingWidth = 30.f;
	
	UPROPERTY(EditAnywhere, Category="Shockwave")
	float ExpandSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category="Shockwave")
	float AcceptanceZ = 10.f;
	
	
	float CurrentRadius;
private:
	bool bDidHitPlayer = false;
	
	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditAnywhere, Category="Shockwave")
	UNiagaraSystem* ShockwaveNiagaraEffect;

	UPROPERTY(EditAnywhere, Category="Shockwave")
	UNiagaraComponent* ShockwaveNiagaraComponent;

	UPROPERTY(EditAnywhere, Category="Shockwave")
	float EffectSize = 0.f;
	
	UPROPERTY()
	float Damage = 0.f;

	TWeakObjectPtr<UAbilitySystemComponent> SourceASC;
	bool CanHitTarget(AActor* Target) const;
	bool TargetInWidth(AActor* Target) const;
	bool IsTargetValid(AActor* Target) const;
	void DebugDraw() const;
	void ApplyDamage(AActor* OtherActor);

	UPROPERTY()
	TArray<AActor*> OverlappingTargets;

};
