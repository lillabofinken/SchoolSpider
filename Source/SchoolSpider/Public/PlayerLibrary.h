// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlayerLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SCHOOLSPIDER_API UPlayerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION( BlueprintCallable, Category = "PlayerNodes" )
			static FVector PlayerVelocity( float _max_velocity, FVector _current_velocity, float _change_amount );

		UFUNCTION( BlueprintCallable, Category = "PlayerNodes" )
			static FVector DynamicCameraOffset( FVector _velocity, FVector _offsetSpeed, FVector _multiplier, float _deltaTime, FVector _currentPosition );
};
