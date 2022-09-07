// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_Dialogue.h"

#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Level/LevelManager.h"


void ATriggerVolume_Dialogue::BeginPlay()
{
	ATriggerVolume_Base::BeginPlay();

	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );

	// Get the level manager that was initialised in the base class.
	m_pcLevelManager = &GetLevelManager();

	// Is this trigger volume triggerable on time type.
	if( m_bTriggerableOnTimeType )
	{
		// Bind the function to on changed day delegate.
		m_pcLevelManager->OnChangedDay.AddUObject( this, &ATriggerVolume_Dialogue::OnChangedDay );
	}

	// Setup an OnComponentBeginOverlap and OnComponentEndOverlap callback functions to be called when an overlap begins.
	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_Dialogue::OnBeginOverlapTrigger );
}

void ATriggerVolume_Dialogue::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	// Check if the actor is not another TriggerVolume_Dialogue and if the actor contains a tag of player.
	// This will detect the player if it has that tag.
	if( ( OtherActor != this ) && OtherActor->Tags.Contains( "Player" ) )
	{
		// Initialise dialogue sequence based on the ID the trigger volume holds.
		m_pcDialogueManager->InitialiseDialogueSequence( m_nDialogueID );
	}
}

void ATriggerVolume_Dialogue::OnChangedDay()
{
	// Check if the current day time type is the same as the one to trigger on.
	if( m_pcLevelManager->GetCurrentDayTimeType() == m_eDayToTrigger )
	{
		// Set collision to be querly only.
		m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
	}
	else
	{
		// Disable collision.
		m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	}
}
