// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BTGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreePerSecond = 20.0F;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegree = 35.0F;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegree = 0.0F;
};
