// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class ECountDownActionOutput : uint8;
/**
 * 
 */
class WUKONG_API FWK_CoolDownTimer : public FPendingLatentAction
{
public:
	FWK_CoolDownTimer(float InTotalCountTime,float InUpdateInterval,float& InOutRemainingTime,ECountDownActionOutput& InCountDownOutput,
		const FLatentActionInfo& LatentInfo, bool bReverse)
	: bNeedCancel(false)
	, TotalCountDownTime(InTotalCountTime)
	, UpdateInterval(InUpdateInterval)
	, OutRemainingTime(InOutRemainingTime)
	, CountDownOutput(InCountDownOutput)
	, ExecutionFunction(LatentInfo.ExecutionFunction)
	, OutputLink(LatentInfo.Linkage)
	, CallbackTarget(LatentInfo.CallbackTarget)
	, ElapsedInterval(0.f)
	, ElapsedTimeSinceStart(0.f)
	, bReverse(bReverse)
	{}
	void CancelAction();

	virtual void UpdateOperation(FLatentResponse& Response) override;
private:
	bool bNeedCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	ECountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
	bool bReverse;
};

