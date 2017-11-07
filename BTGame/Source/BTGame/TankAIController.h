// Copyright Matias Fuentes.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/World.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class BTGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Setup)
	float AcceptanceRadius = 6000.0F; // How Close Can Get To The Enemy Position.

	APawn* EnemyTarget;
	APawn* ControlledTank;
};
