// SpawnActor.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

UCLASS()
class P3P4_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	TSubclassOf<AActor> RotatingActorClass;
	
	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	TSubclassOf<AActor> MovingActorClass;
	
	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	int32 SpawnCount;
	
};
