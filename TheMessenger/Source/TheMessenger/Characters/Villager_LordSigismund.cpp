// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_LordSigismund.h"

#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Menus/DayEndScreen.h"
#include "TheMessenger/TheMessengerCharacter.h"

void AVillager_LordSigismund::BeginPlay()
{
	// Call the villager base class begin play.
	AVillager_Base::BeginPlay();

	// Create the day end screen and add it to viewport
	m_pcDayEndScreen = CreateWidget<UDayEndScreen>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), m_tcDayEndScreen );
	m_pcDayEndScreen->AddToViewport();
}

void AVillager_LordSigismund::OnDialogueFinished()
{
	// Get if Lord was interacted.
	if( GetInteracted() )
	{
		// Call the base class of on dialogue finished.
		AVillager_Base::OnDialogueFinished();

		// Display the day end screen.
		m_pcDayEndScreen->DisplayScreen();
	}
}

void AVillager_LordSigismund::OnInteract_Implementation( AActor* Caller )
{
	// Call the base class of on interact to set the player's position.
	AVillager_Base::OnInteract_Implementation( Caller );

	// Then set the player being in end day sequence.
	GetPlayer().SetInEndDaySequence( true );
}
