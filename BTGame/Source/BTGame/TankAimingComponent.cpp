// Copyright Matias Fuentes.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TyckType, FActorComponentTickFunction* ThisTickFunction)
{
	if (AmountOfProjectiles > 0)
	{
		if ((GetWorld()->GetTimeSeconds() - LastTimeFired) < ReloadTimeInSeconds)
			FiringStatus = EFiringStatus::Reloading;
		else if (IsAimBarrelMoving())
			FiringStatus = EFiringStatus::Aiming;
		else
			FiringStatus = EFiringStatus::Locked;
	}
	else
		FiringStatus = EFiringStatus::NoAmmo;
}

void UTankAimingComponent::BeginPlay()
{
	LastTimeFired = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	UTankAimingComponent::AimBarrel = BarrelToSet;
	UTankAimingComponent::AimTurret = TurretToSet;
}

bool UTankAimingComponent::IsAimBarrelMoving()
{
	if (!ensure(AimBarrel)) { return false; }

	FVector CurrentBarrelForward = AimBarrel->GetForwardVector();
	return !CurrentBarrelForward.Equals(AimDirection, 0.1F);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(AimBarrel)) { return; }

	FVector LaunchVelocity;
	FVector StartLocation = AimBarrel->GetSocketLocation(FName("Shooting Point"));

	// Calculate The Launch Velocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OUT LaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.0F, 0.0F, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		AimDirection = LaunchVelocity.GetSafeNormal();
		UTankAimingComponent::MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(AimBarrel || !ensure(AimTurret))) { return; }

	FRotator BarrelRotator = AimBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	AimBarrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180.0F)
		AimTurret->Rotate(DeltaRotator.Yaw);
	else
		AimTurret->Rotate(-DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus == EFiringStatus::Locked || FiringStatus == EFiringStatus::Aiming)
	{
		if (!ensure(AimBarrel)) return;
		if (!ensure(ProjectileBlueprint)) return;

		FVector ProjectileLocation = AimBarrel->GetSocketLocation(FName("Shooting Point"));
		FRotator ProjectileRotation = AimBarrel->GetSocketRotation(FName("Shooting Point"));

		//Spawn Projectile At The Socket Location On The Barrel
		AProjectile* CurrentProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);
		CurrentProjectile->Launch(LaunchSpeed);
		LastTimeFired = GetWorld()->GetTimeSeconds();

		--AmountOfProjectiles;
	}
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const { return FiringStatus; }

int32 UTankAimingComponent::GetAmountOfProjectiles() { return AmountOfProjectiles; }