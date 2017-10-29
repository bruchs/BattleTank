// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
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

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if(AimBarrel != nullptr)
	{
		FVector LaunchVelocity;
		FVector StartLocation = AimBarrel->GetSocketLocation(FName("Shooting Point"));

		// Calculate The Launch Velocity
		if (UGameplayStatics::SuggestProjectileVelocity(this, OUT LaunchVelocity, StartLocation, HitLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace))
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

	UE_LOG(LogTemp, Warning, TEXT("Aim As Rotator: %s"), *AimAsRotator.ToString());

	AimBarrel->Elevate(5.0F); // TODO Remove Magic Number.
}