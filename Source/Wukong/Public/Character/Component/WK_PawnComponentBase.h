// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WK_PawnComponentBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WUKONG_API UWK_PawnComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWK_PawnComponentBase();

protected:
	template<class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T,APawn>::Value, TEXT("Template parameter must be convertible from APawn"));
		return CastChecked<T>(GetOwner());
	}
	
	APawn* GetOwningPawn() const
	{
		return CastChecked<APawn>(GetOwner());
	}
	
	template<class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T,AController>::Value, TEXT("Template parameter must be convertible from AController"));
		return GetOwningPawn<APawn>()->GetController();
	}
		
};
