// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move The Barrel The Right Amount This Frame.
	// Clamp The Relative Speed So The Barrel Always Move At The Same Speed.
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0F, 1.0F);

	float ElevationChange = RelativeSpeed * UTankBarrel::MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + ElevationChange;

	float FinalElevation = FMath::Clamp(NewElevation, UTankBarrel::MinElevationDegree, UTankBarrel::MaxElevationDegree);
	SetRelativeRotation(FRotator(FinalElevation, 0.0F, 0.0F));
}