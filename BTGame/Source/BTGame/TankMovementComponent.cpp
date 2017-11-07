// Copyright Matias Fuentes.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) return;

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& Speed, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector();
	FVector AIForwardIntention = Speed.GetSafeNormal();

	float MovementSpeed = FVector::DotProduct(TankForward, AIForwardIntention);
	FVector MovementRotation = FVector::CrossProduct(TankForward, AIForwardIntention);
	
	IntendMoveForward(MovementSpeed);
	IntendTurnRight(MovementRotation.Z);
}