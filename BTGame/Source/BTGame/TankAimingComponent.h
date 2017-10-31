// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BTGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	
	void AimAt(FVector HitLocation, float LaunchSpeed);
	void SetAimBarrelReference(UTankBarrel* AimBarrel);
	void SetAimTurretReference(UTankTurret* AimTurret);

private:
	UTankBarrel* AimBarrel = nullptr;
	UTankTurret* AimTurret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
};
