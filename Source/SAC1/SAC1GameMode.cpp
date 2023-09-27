// Copyright Epic Games, Inc. All Rights Reserved.

#include "SAC1GameMode.h"
#include "SAC1Character.h"
#include "UObject/ConstructorHelpers.h"

ASAC1GameMode::ASAC1GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
