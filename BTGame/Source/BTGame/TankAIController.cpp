// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get The Player Tank.
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	EnemyTarget = Cast<ATank>(PlayerPawn);
	
	if(EnemyTarget != nullptr)
	{
		FVector HitLocation = EnemyTarget->GetActorLocation();
		ControlledTank->AimAt(HitLocation);
		ControlledTank->Fire();
	}
}