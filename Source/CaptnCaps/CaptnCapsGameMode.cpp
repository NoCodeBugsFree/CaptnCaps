// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "CaptnCaps.h"
#include "CaptnCapsGameMode.h"
#include "CaptnCapsPlayerController.h"
#include "CaptnCapsCharacter.h"

ACaptnCapsGameMode::ACaptnCapsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACaptnCapsPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}