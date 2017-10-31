// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Tank.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = ATankAIController::GetControlledTank();
	ATankAIController::EnemyTarget = ATankAIController::GetPlayerTank();

	if(ControlledTank != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Enemy AI ID: %S"), *(ControlledTank->GetName()));

	if (EnemyTarget != nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Player Tank ID: %S"), *(EnemyTarget->GetName()));
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(ATankAIController::EnemyTarget != nullptr)
	{
		FVector HitLocation = ATankAIController::EnemyTarget->GetActorLocation();
		GetControlledTank()->AimAt(HitLocation);
	}
}