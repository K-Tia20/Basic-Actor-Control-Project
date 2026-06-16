// SpawnActor.cpp


#include "Actor/SpawnActor.h"
#include "Actor/RotatingActor.h"
#include "Actor/MovingActor.h"


ASpawnActor::ASpawnActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SpawnCount = 30;
}

void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < SpawnCount; i++)
	{
		FVector RandomLocation = FVector(FMath::RandRange(-1500.0f, 1500.0f), FMath::RandRange(-1500.0f, 1500.0f), 200.0f);
		FRotator RandomRotation = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);
	
		if (RotatingActorClass)
		{
			ARotatingActor* NewRotator = GetWorld()->SpawnActor<ARotatingActor>(RotatingActorClass, RandomLocation, RandomRotation);
			if (NewRotator)
			{
				NewRotator->RotationSpeed = FMath::RandRange(30.0f, 200.0f);
			}
		}
		
		RandomLocation.Y += 300.0f;
		RandomLocation.Z = 20.0f;
		
		if (MovingActorClass)
		{
			AMovingActor* NewMover = GetWorld()->SpawnActor<AMovingActor>(MovingActorClass, RandomLocation, FRotator::ZeroRotator);
			if (NewMover)
			{
				NewMover->MoveSpeed = FMath::RandRange(100.0f, 400.0f);
				NewMover->MaxRange = FMath::RandRange(200.0f, 600.0f);
			}
		}
	}		
}


