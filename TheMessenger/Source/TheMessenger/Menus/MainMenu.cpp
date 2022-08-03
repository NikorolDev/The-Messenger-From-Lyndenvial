// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

void UMainMenu::NativeConstruct()
{
	//m_pcIntroCinematic = CreateWidget<UUserWidget>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), 
	//												m_tcIntroCinematic );

	NewGameButton->OnClicked.AddDynamic( this, &UMainMenu::NewGameButtonClicked );
}

void UMainMenu::NewGameButtonClicked()
{
	SetVisibility( ESlateVisibility::Hidden );
	//m_pcIntroCinematic->AddToViewport();
	InitiateCinematic();
}

void UMainMenu::ContinueButtonClicked()
{
}

void UMainMenu::QuitButtonClicked()
{
}
