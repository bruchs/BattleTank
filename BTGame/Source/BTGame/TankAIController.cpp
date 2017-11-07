// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = GetPawn();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get The Player Tank.
	EnemyTarget = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!ensure(EnemyTarget && ControlledTank)) { return; }
	MoveToActor(EnemyTarget, AcceptanceRadius);

	UTankAimingComponent* AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation = EnemyTarget->GetActorLocation();
	AimingComponent->AimAt(HitLocation);

	if(AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
		AimingComponent->Fire();
}