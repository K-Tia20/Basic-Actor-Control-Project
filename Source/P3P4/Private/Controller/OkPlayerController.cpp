// OkPlayerController.cpp


#include "Controller/OkPlayerController.h"
#include "EnhancedInputSubsystems.h"

AOkPlayerController::AOkPlayerController()
	: InputMappingContext(nullptr),
	  MoveAction(nullptr),
	  LookAction(nullptr),
	  MoveUpAction(nullptr),
	  MoveDownAction(nullptr),
	  RollAction(nullptr)
{
}

void AOkPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}