// Copyright Matias Fuentes.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
		FoundAimingComponent(AimingComponent);
	else
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Can't Find Aiming Component"));
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }

	UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FVector HitLocation;

	if(ATankPlayerController::GetSightRayHitLocation(HitLocation))
	{
		// We Get Our Reference To Our Tank.
		AimingComponent->AimAt(HitLocation);
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