// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_Sequence.h"

#include <Components/BoxComponent.h>
#include <LevelSequence/Public/LevelSequenceActor.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>

#include "TheMessenger/Characters/Villager_Base.h"
#include "TheMessenger/Level/LevelManager.h"
#include "TheMessenger/TheMessengerCharacter.h"

void ATriggerVolume_Sequence::BeginPlay()
{
	// Call the base class's begin play function, which would be the AActor's one as the TriggerVolume_Base does not have one.
	ATriggerVolume_Base::BeginPlay();

	// Create default sequence playback settings.
	FMovieSceneSequencePlaybackSettings m_pfsLevelSequencePlaybackSettings;

	// If a level sequence has been set in the editor
	if( m_pcLevelSequenceToPlay != nullptr )
	{
		// Create level sequence player, to play the level sequence.
		m_pcLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer( GetWorld(), m_pcLevelSequenceToPlay->GetSequence(), m_pfsLevelSequencePlaybackSettings, m_pcLevelSequenceToPlay );
	}

	// Get the level manager that was initialised in the base class.
	m_pcLevelManager = &GetLevelManager();

	// Check if trigger volumes is triggerd is on a certain day.
	if( m_bTriggerOnDay )
	{
		// Bind the function to on changed day delegate.
		m_pcLevelManager->OnChangedDay.AddUObject( this, &ATriggerVolume_Sequence::OnChangedDay );
	}

	// Setup an OnComponentBeginOverlap callback function to be called when an overlap is triggered.
	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_Sequence::OnBeginOverlapTrigger );
}

void ATriggerVolume_Sequence::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	// Check if the actor is not another TriggerVolume_EndGame and if the actor contains a tag of player.
	// This will detect the player if it has that tag.
	if( ( OtherActor != this ) && OtherActor->Tags.Contains( "Player" ) )
	{
		// Get the player from the actor that was collided and disable player input.
		ATheMessengerCharacter* Player = Cast<ATheMessengerCharacter>( OtherActor );

		// Check if it's triggerd on any day.
		if( m_bTriggerOnDay )
		{
			// Turn off collision. To not be called again.
			m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::NoCollision );
		}

		// Check if the villager has been set in the editor.
		if( m_pcVillagerToInteract != nullptr )
		{
			if( m_pcVillagerToInteract->GetActive() )
			{
				//Call the interaction function from the charatcer.
				m_pcVillagerToInteract->OnInteract_Implementation( this );
				Player->DisableInput( &Player->GetPlayerController() );
			}
		}

		// Check if the level sequencer has been set
		if( m_pcLevelSequenceToPlay != nullptr )
		{
			// Play the level sequencer.
			m_pcLevelSequencePlayer->Play();
		}
	}
}

void ATriggerVolume_Sequence::OnImpactActor_Implementation()
{
	// Enable collision.
	m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
}

void ATriggerVolume_Sequence::OnChangedDay()
{
	if( m_bTriggerOnDay )
	{
		// Check if the day to trigger is the same as the current day.
		if( m_iDayToTrigger == m_pcLevelManager->GetDayID() )
		{
			// Enable collision.
			m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
		}
		else
		{
			// Disable collision.
			m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::NoCollision );
		}
	}
}
