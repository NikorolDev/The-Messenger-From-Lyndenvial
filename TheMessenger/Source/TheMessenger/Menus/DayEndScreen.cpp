// Fill out your copyright notice in the Description page of Project Settings.


#include "DayEndScreen.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Endings/EndingManager.h"
#include "TheMessenger/Level/LevelManager.h"

void UDayEndScreen::NativeConstruct()
{
	SetVisibility( ESlateVisibility::Hidden );

	m_pcEndingManager = Cast<AEndingManager>( UGameplayStatics::GetActorOfClass( GetWorld(), AEndingManager::StaticClass() ) );
	m_pcLevelManager = Cast<ALevelManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ALevelManager::StaticClass() ) );


	Continue->OnClicked.AddDynamic( this, &UDayEndScreen::OnContinueClicked );
	MainMenu->OnClicked.AddDynamic( this, &UDayEndScreen::OnMainMenuClicked );
}

void UDayEndScreen::OnContinueClicked()
{
	m_pcLevelManager->SetNewDay();
	SetVisibility( ESlateVisibility::Hidden );
}

void UDayEndScreen::OnMainMenuClicked()
{
	UGameplayStatics::OpenLevel( GetWorld(), "Map_MainMenu" );
}

void UDayEndScreen::DisplayScreen()
{
	if( !m_pcEndingManager->DisplayEnding() )
	{
		APlayerController* pcPlayerController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );

		pcPlayerController->SetInputMode( FInputModeUIOnly() );
		pcPlayerController->bShowMouseCursor = true;
		SetVisibility( ESlateVisibility::Visible );
	}
}
