// OkPawn.cpp


#include "Pawn/OkPawn.h"
#include "Controller/OkPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"

AOkPawn::AOkPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	CapsuleComp->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComp->SetSimulatePhysics(false); 

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	MoveInputVector = FVector::ZeroVector;
	LookInputVector = FVector::ZeroVector;
}

void AOkPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOkPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
    FHitResult HitResult;
    FVector StartLocation = GetActorLocation();

    float TraceLength = CapsuleComp->GetScaledCapsuleHalfHeight() + 5.0f;
    FVector EndLocation = StartLocation - FVector(0.0f, 0.0f, TraceLength);

    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, TraceParams);

    if (bHit)
    {
        bIsGrounded = true;
        if (VerticalVelocity < 0.0f)
        {
            VerticalVelocity = 0.0f;
        }
    }
    else
    {
        bIsGrounded = false;
        VerticalVelocity += Gravity * DeltaTime;
    }

    float CurrentSpeed = bIsGrounded ? MoveSpeed : MoveSpeed * 0.4f;

    FVector InstantMove = MoveInputVector * CurrentSpeed * DeltaTime;
    
    AddActorLocalOffset(InstantMove, true);

    AddActorWorldOffset(FVector(0.0f, 0.0f, VerticalVelocity * DeltaTime), true);

    FRotator PawnRotation = FRotator(0.0f, LookInputVector.X, LookInputVector.Z);
    AddActorLocalRotation(PawnRotation);

    FRotator NewArmRotation = SpringArmComp->GetRelativeRotation();
    NewArmRotation.Pitch = FMath::Clamp(NewArmRotation.Pitch + LookInputVector.Y, -60.0f, 60.0f); 
    SpringArmComp->SetRelativeRotation(NewArmRotation);

    MoveInputVector = FVector::ZeroVector;
    LookInputVector = FVector::ZeroVector;
}


void AOkPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (AOkPlayerController* PC = Cast<AOkPlayerController>(GetController()))
        {
            if (PC->MoveAction)
                EnhancedInput->BindAction(PC->MoveAction, ETriggerEvent::Triggered, this, &AOkPawn::Move);
            
            if (PC->LookAction)
                EnhancedInput->BindAction(PC->LookAction, ETriggerEvent::Triggered, this, &AOkPawn::Look);

            if (PC->MoveUpAction)
                EnhancedInput->BindAction(PC->MoveUpAction, ETriggerEvent::Triggered, this, &AOkPawn::MoveUp);

            if (PC->MoveDownAction)
                EnhancedInput->BindAction(PC->MoveDownAction, ETriggerEvent::Triggered, this, &AOkPawn::MoveDown);

            if (PC->RollAction)
                EnhancedInput->BindAction(PC->RollAction, ETriggerEvent::Triggered, this, &AOkPawn::RollAxis);
        }
    }
}

void AOkPawn::Move(const FInputActionValue& Value)
{
    FVector2D Input = Value.Get<FVector2D>();
    MoveInputVector.X = Input.Y; 
    MoveInputVector.Y = Input.X;
}

void AOkPawn::MoveUp(const FInputActionValue& Value)
{
    MoveInputVector.Z = 1.0f;
}

void AOkPawn::MoveDown(const FInputActionValue& Value)
{
    MoveInputVector.Z = -1.0f;
}

void AOkPawn::Look(const FInputActionValue& Value)
{
    FVector2D Input = Value.Get<FVector2D>();
    LookInputVector.X = Input.X; 
    LookInputVector.Y = -Input.Y; 
}

void AOkPawn::RollAxis(const FInputActionValue& Value)
{
    LookInputVector.Z = Value.Get<float>() * 5.0f; 
}