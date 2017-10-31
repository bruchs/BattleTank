// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move The Turret The Right Amount This Frame.
	// Clamp The Relative Speed So The Turret Always Move At The Same Speed.
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0F, 1.0F);

	float RotationChange = RelativeSpeed * UTankTurret::MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;
	float FinalRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.0F, FinalRotation, 0.0F));
}