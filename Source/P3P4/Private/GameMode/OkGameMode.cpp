// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/OkGameMode.h"
#include "Pawn/OkPawn.h"
#include "Controller/OkPlayerController.h"

AOkGameMode::AOkGameMode()
{
	DefaultPawnClass = AOkPawn::StaticClass();
    
	PlayerControllerClass = AOkPlayerController::StaticClass();
}