// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicatingMovement(true);

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

	// This was the old client version way to set replicates
	//if (HasAuthority()) 
	//{
	//	SetReplicates(true);
	//	SetReplicateMovement(true);
	//}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector Location = GetActorLocation();
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
			float JourneyTravelled = (Location - GlobalStartLocation).Size();

			if (JourneyTravelled >= JourneyLength)
			{
				FVector Swap = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Swap;
			}

			Location += PlatformSpeed * DeltaTime * Direction;
			SetActorLocation(Location);

			/*
			// Lets me see the logic
			UE_LOG(LogTemp, Warning, TEXT("GlobalStartLocation = %s"), *GlobalStartLocation.ToString());
			UE_LOG(LogTemp, Warning, TEXT("GlobalTargetLocation = %s"), *GlobalTargetLocation.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Direction = %s"), *Direction.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Current MovingPlatform Location = %s"), *Location.ToString());
			UE_LOG(LogTemp, Warning, TEXT("Journey Length = %f"), JourneyLength);
			UE_LOG(LogTemp, Warning, TEXT("Journey travelled = %f"), JourneyTravelled);
			*/
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		ActiveTriggers--;
	}
}
