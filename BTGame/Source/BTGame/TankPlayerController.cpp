// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#define OUT

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank() == nullptr)
		return;
	
	FVector HitLocation;

	if(ATankPlayerController::GetSightRayHitLocation(HitLocation))
	{
		// We Get Our Reference To Our Tank.
		GetControlledTank()->AimAt(HitLocation);
	}
}

// Get World Location Of Linetrace Through The UI Crosshair.
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find The Crosshair Position In Pixel Coordinates.
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-Project" The Screen Position Of The Crosshair To A World Direction.
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace Along That LookDirection, And See What We Hit.
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLoc, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLoc.X, ScreenLoc.Y, CameraWorldLocation, OUT LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0.0f);
	return false;
}
