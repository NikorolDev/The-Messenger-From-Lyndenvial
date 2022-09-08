// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

#include "Cinematic.h"

void UMainMenu::NativeConstruct()
{
	// Calls the native construct from UUserWidget.
	Super::NativeConstruct();

	// Create the cinematic widget and add it to viewport.
	m_pcCinematicWidget = CreateWidget<UCinematic>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ),
													m_tcCinematicWidget );
	m_pcCinematicWidget->AddToViewport();

	// As this is the main menu, the cinematic has been accessed by the main menu to open the game map.
	m_pcCinematicWidget->SetAccessedFromMainMenu( true );

	// Bind to the main menu buttons.
	NewGameButton->OnClicked.AddDynamic( this, &UMainMenu::NewGameButtonClicked );
	QuitButton->OnClicked.AddDynamic( this, &UMainMenu::QuitButtonClicked );
}

void UMainMenu::NewGameButtonClicked()
{
	// Hide the main menu and play the intro cinematic.
	SetVisibility( ESlateVisibility::Hidden );
	m_pcCinematicWidget->PlayCinematic( m_pfsIntroCinematic );
}

void UMainMenu::QuitButtonClicked()
{
	// Close the game down.
	UKismetSystemLibrary::QuitGame( GetWorld(), UGameplayStatics::GetPlayerController( GetWorld(), 0 ), EQuitPreference::Quit, false );
}
