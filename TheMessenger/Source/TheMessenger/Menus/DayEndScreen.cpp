// Fill out your copyright notice in the Description page of Project Settings.


#include "DayEndScreen.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Endings/EndingManager.h"
#include "TheMessenger/Level/LevelManager.h"

void UDayEndScreen::NativeConstruct()
{
	// Hide the widget.
	SetVisibility( ESlateVisibility::Hidden );

	// Get the ending manager and the level maanger.
	m_pcEndingManager = Cast<AEndingManager>( UGameplayStatics::GetActorOfClass( GetWorld(), AEndingManager::StaticClass() ) );
	m_pcLevelManager = Cast<ALevelManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ALevelManager::StaticClass() ) );

	// Bind the buttons to respond to the being clicked.
	Continue->OnClicked.AddDynamic( this, &UDayEndScreen::OnContinueClicked );
	MainMenu->OnClicked.AddDynamic( this, &UDayEndScreen::OnMainMenuClicked );
}

void UDayEndScreen::OnContinueClicked()
{
	// Set a new day and hide the widget.
	m_pcLevelManager->SetNewDay();
	SetVisibility( ESlateVisibility::Hidden );
}

void UDayEndScreen::OnMainMenuClicked()
{
	// Open the main menu map.
	UGameplayStatics::OpenLevel( GetWorld(), "Map_MainMenu" );
}

void UDayEndScreen::DisplayScreen()
{
	// Check if the ending can't be displayed.
	if( !m_pcEndingManager->DisplayEnding() )
	{
		// Get the player controller and set the input to UI only and show the cursor
		APlayerController* pcPlayerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
		pcPlayerController->SetInputMode( FInputModeUIOnly() );
		pcPlayerController->bShowMouseCursor = true;

		// Set the widget to be visible.
		SetVisibility( ESlateVisibility::Visible );
	}
}
