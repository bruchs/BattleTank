// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetAimBarrelReference(UTankBarrel* AimBarrel)
{
	UTankAimingComponent::AimBarrel = AimBarrel;
}

void UTankAimingComponent::SetAimTurretReference(UTankTurret* AimTurret)
{
	UTankAimingComponent::AimTurret = AimTurret;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if(AimBarrel != nullptr)
	{
		FVector LaunchVelocity;
		FVector StartLocation = AimBarrel->GetSocketLocation(FName("Shooting Point"));

		// Calculate The Launch Velocity
		if (UGameplayStatics::SuggestProjectileVelocity(this, OUT LaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.0F, 0.0F, ESuggestProjVelocityTraceOption::DoNotTrace))
		{
			FVector AimDirection = LaunchVelocity.GetSafeNormal();
			UTankAimingComponent::MoveBarrelTowards(AimDirection);
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = AimBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	AimBarrel->Elevate(DeltaRotator.Pitch);
	AimTurret->Rotate(DeltaRotator.Yaw);
}