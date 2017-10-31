// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if(TankBarrel != nullptr)
	{
		FVector ProjectileLocation = TankBarrel->GetSocketLocation(FName("Shooting Point"));
		FRotator ProjectileRotation = TankBarrel->GetSocketRotation(FName("Shooting Point"));

		//Spawn Projectile At The Socket Location On The Barrel
		GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);
	}
	else
		return;
}

void ATank::SetAimBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetAimBarrelReference(BarrelToSet);
	TankBarrel = BarrelToSet;
}

void ATank::SetAimTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetAimTurretReference(TurretToSet);
}