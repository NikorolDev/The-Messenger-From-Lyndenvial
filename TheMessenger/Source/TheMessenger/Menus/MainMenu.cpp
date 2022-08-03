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

	NewGameButton->OnClicked.AddDynamic( this, &UMainMenu::NewGameButtonClicked );
}

void UMainMenu::NewGameButtonClicked()
{
	SetVisibility( ESlateVisibility::Hidden );
	m_pcCinematicWidget->AddToViewport();
	m_pcCinematicWidget->PlayCinematic( m_pcIntroCinematicMaterial, m_pcIntroCinematicPlayer );
}

void UMainMenu::ContinueButtonClicked()
{
}

void UMainMenu::QuitButtonClicked()
{
}
