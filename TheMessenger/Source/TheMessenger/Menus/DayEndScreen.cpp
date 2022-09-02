// Fill out your copyright notice in the Description page of Project Settings.


#include "DayEndScreen.h"

#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Level/LevelManager.h"

void UDayEndScreen::NativeConstruct()
{
	SetVisibility( ESlateVisibility::Hidden );

	m_pcLevelManager = Cast<ALevelManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ALevelManager::StaticClass() ) );

	Continue->OnClicked.AddDynamic( this, &UDayEndScreen::OnContinueClicked );
}

void UDayEndScreen::OnContinueClicked()
{
	m_pcLevelManager->SetNewDay();
	SetVisibility( ESlateVisibility::Hidden );
}

void UDayEndScreen::OnMainMenuClicked()
{
}

void UDayEndScreen::DisplayScreen()
{
	SetVisibility( ESlateVisibility::Visible );
}
