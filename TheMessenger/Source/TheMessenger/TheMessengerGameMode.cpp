// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheMessengerGameMode.h"

#include <Kismet/GameplayStatics.h>

#include "TheMessengerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheMessengerGameMode::ATheMessengerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATheMessengerGameMode::BeginPlay()
{
	APlayerController* pcPlayerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
	pcPlayerController->bShowMouseCursor = false;
	pcPlayerController->SetInputMode( FInputModeGameOnly() );
}
