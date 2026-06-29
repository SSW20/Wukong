#pragma once

UENUM(BlueprintType)
enum class EActorDirection : uint8
{
	Forward,
	Left,
	Right,
	Back,
	None,
};

UENUM(BlueprintType)
enum class EDistanceToTarget : uint8
{
	TooFar,
	Far,
	Middle,
	Close,
	TooClose
};

UENUM(BlueprintType)
enum class ECountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM()
enum class ECountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EHitReactLevel : uint8
{
	Shrink,
	Light,
	Heavy
};