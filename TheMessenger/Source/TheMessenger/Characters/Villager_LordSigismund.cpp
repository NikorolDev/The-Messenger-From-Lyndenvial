// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_LordSigismund.h"

#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Menus/DayEndScreen.h"
#include "TheMessenger/TheMessengerCharacter.h"

void AVillager_LordSigismund::BeginPlay()
{
	AVillager_Base::BeginPlay();

	m_pcDayEndScreen = CreateWidget<UDayEndScreen>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), m_tcDayEndScreen );
	m_pcDayEndScreen->AddToViewport( 0 );
}

void AVillager_LordSigismund::OnDialogueFinished()
{
	if( GetInteracted() )
	{
		AVillager_Base::OnDialogueFinished();

		m_pcDayEndScreen->DisplayScreen();
	}
}

void AVillager_LordSigismund::OnInteract_Implementation( AActor* Caller )
{
	AVillager_Base::OnInteract_Implementation( Caller );
	GetPlayer().SetInEndDaySequence( true );
}
