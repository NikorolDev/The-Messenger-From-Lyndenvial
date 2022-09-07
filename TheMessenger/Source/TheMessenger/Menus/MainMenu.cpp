// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

#include "Cinematic.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	m_pcCinematicWidget = CreateWidget<UCinematic>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ),
													m_tcCinematicWidget );
	m_pcCinematicWidget->AddToViewport();
	m_pcCinematicWidget->SetAccessedFromMainMenu( true );

	NewGameButton->OnClicked.AddDynamic( this, &UMainMenu::NewGameButtonClicked );
	QuitButton->OnClicked.AddDynamic( this, &UMainMenu::QuitButtonClicked );
}

void UMainMenu::NewGameButtonClicked()
{
	SetVisibility( ESlateVisibility::Hidden );
	m_pcCinematicWidget->PlayCinematic( m_pfsIntroCinematic );
}

void UMainMenu::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame( GetWorld(), UGameplayStatics::GetPlayerController( GetWorld(), 0 ), EQuitPreference::Quit, false );
}
