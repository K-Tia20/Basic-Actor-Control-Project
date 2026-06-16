// RotatingActor.cpp


#include "Actor/RotatingActor.h"

ARotatingActor::ARotatingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
	
	RotationSpeed = 90.0f;
}

void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TeleportTimerHandle, this, &ARotatingActor::TeleportRandomly, 5.0f, true);

}

void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}
}

void ARotatingActor::TeleportRandomly()
{
	FVector CurrentLocation = GetActorLocation();
	
	CurrentLocation.X += FMath::RandRange(-200.0f, 200.0f);
	CurrentLocation.Y += FMath::RandRange(-200.0f, 200.0f);
	
	SetActorLocation(CurrentLocation);
}