// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_Damage.h"

#include "WK_GameplayTags.h"
#include "AbilitySystem/WK_AttributeSet.h"
#include "EnvironmentQuery/Tests/EnvQueryTest_GameplayTags.h"

struct FWKDamageCapture
{
	//FProperty*와 FGameplayEffectAttributeCaptureDefinition 변수를 선언
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	// 선언된 능력치 캡처 정의를 구체적으로 초기화합니다.
	// S: 해당 능력치가 속한 AttributeSet 클래스 
	// P: 능력치 이름 
	// T: 능력치를 누구로부터 캡처할지 (Target - 피해자로부터 가져옴)
	// B: 스냅샷(Snapshot) 여부 (false - 즉시 적용 시점의 값을 가져옴)
	FWKDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWK_AttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWK_AttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWK_AttributeSet, Damage, Source, false);
	}
};

static const FWKDamageCapture& GetDamageCapture()
{
	static FWKDamageCapture DamageCapture;
	return DamageCapture;
}

UGEExecCalc_Damage::UGEExecCalc_Damage()
{
	// RelevantAttributesToCapture 배열에 추가된 능력치들만 ExecutionParams.AttemptCalculateCapturedAttributeMagnitude를 통해 캡처할 수 있음
	RelevantAttributesToCapture.Add(GetDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DamageDef);
}

void UGEExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// ExecutionParams: GE 실행에 필요한 모든 입력 정보 (소스, 타겟, GE 스펙 등)를 담고 있는 구조체.
	// OutExecutionOutput: 계산된 최종 결과를 GAS 시스템에 전달하여 능력치를 실제로 변경하는 데 사용되는 출력 구조체

	// ExecutionParams을 통해 ASC를 가져옴 
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	// ASC를 가져오면 ASC를 가지는 액터를 가져올 수 있음
	AActor* SourceActor =  SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	//ExecutionParams을 통해 GameplayEffectSpec(GE의 설계도)을 가져옴 
	const FGameplayEffectSpec EffectSpec = ExecutionParams.GetOwningSpec();

	//EffectSpec에서 Source와 Target에 붙어 있는 Gameplay Tag들을 가져옴
	const FGameplayTagContainer* SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	//능력치 평가에 필요한 파라미터 구조체인 FAggregatorEvaluateParameters를 초기화
	//능력치 값을 평가할 때 소스/타겟 태그의 영향을 고려
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	const FGameplayEffectContextHandle ContextHandle = EffectSpec.GetContext();

	float SourceAttackPower = 0.f;
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().DefensePowerDef, EvaluateParams, TargetDefensePower);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().AttackPowerDef, EvaluateParams, SourceAttackPower);

	float Damage = EffectSpec.GetSetByCallerMagnitude(WKGameplayTags::SetByCaller_Shared_BaseDamage, true, 0.f);
	float LightAttackComboCount = EffectSpec.GetSetByCallerMagnitude(WKGameplayTags::SetByCaller_Player_AttackType_LigthAttack, false, -1.f);
	float ChargeAttackComboCount = EffectSpec.GetSetByCallerMagnitude(WKGameplayTags::SetByCaller_Player_AttackType_ChargeAttack, false, -1.f);
	float MaxHitCount = EffectSpec.GetSetByCallerMagnitude(WKGameplayTags::SetByCaller_Player_HitCount, false, 1.f);
	
	if (LightAttackComboCount > -1.f)
	{
		Damage *= (LightAttackComboCount * 0.2f + 1.0f);
	}

	if (ChargeAttackComboCount > -1.f)
	{
		Damage *= (ChargeAttackComboCount * 0.5f + 1.0f);
	}

	if (MaxHitCount > 0.f)
	{
		Damage *= (1.f / MaxHitCount);
	}
	
	float TotalDamage = SourceAttackPower * Damage / TargetDefensePower;
	//OutExecutionOutput은 자동으로 Target의 AbilitySystemComponent에 대한 변경 지시를 담는 '컨테이너' 역할을 함
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UWK_AttributeSet::GetDamageAttribute(), EGameplayModOp::Override, TotalDamage));
	
}
