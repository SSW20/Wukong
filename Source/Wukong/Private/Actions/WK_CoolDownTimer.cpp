// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/WK_CoolDownTimer.h"

#include "Kismet/GameplayStatics.h"
#include "Types/WK_EnumTypes.h"

void FWK_CoolDownTimer::CancelAction()
{
	bNeedCancel = true;
}

void FWK_CoolDownTimer::UpdateOperation(FLatentResponse& Response)
{
	if (UGameplayStatics::IsGamePaused(CallbackTarget.Get()))
	{
		// 일시 정지 상태라면 아무 작업도 하지 않고 리턴합니다.
		// ElapsedTimeSinceStart나 ElapsedInterval을 업데이트하지 않습니다.
		return;
	}
	
	if (bNeedCancel)
	{
		CountDownOutput = ECountDownActionOutput::Cancelled;

		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}
	if (ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		CountDownOutput = ECountDownActionOutput::Completed;

		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}

	if (ElapsedInterval < UpdateInterval)
	{
		ElapsedInterval += Response.ElapsedTime();
	}
	else
	{
		// 실제 업데이트 반복
		ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();

		if (bReverse)
		{
			OutRemainingTime = ElapsedTimeSinceStart;
		}
		else
		{
			OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;
		}

		CountDownOutput = ECountDownActionOutput::Updated;

		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);

		ElapsedInterval = 0.f;
	}
}
