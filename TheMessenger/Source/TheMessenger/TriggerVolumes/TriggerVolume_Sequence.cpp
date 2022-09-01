// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_Sequence.h"

#include <Components/BoxComponent.h>
#include <LevelSequence/Public/LevelSequenceActor.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>

#include "TheMessenger/Characters/Villager_Base.h"
#include "TheMessenger/TheMessengerCharacter.h"


void ATriggerVolume_Sequence::BeginPlay()
{
	// Call the base class's begin play function, which would be the AActor's one as the TriggerVolume_Base does not have one.
	Super::BeginPlay();

	// Create default sequence playback settings.
	FMovieSceneSequencePlaybackSettings m_pfsLevelSequencePlaybackSettings;

	if( m_pcLevelSequenceToPlay != nullptr )
	{
		m_pcLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer( GetWorld(), m_pcLevelSequenceToPlay->GetSequence(), m_pfsLevelSequencePlaybackSettings, m_pcLevelSequenceToPlay );
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
		// Turn off collision. To not be called again.
		m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::NoCollision );

		if( m_pcInteractedCharacter != nullptr )
		{
			//Call the interaction function from the charatcer.
			m_pcInteractedCharacter->OnInteract_Implementation( this );
		}

		if( m_pcLevelSequenceToPlay != nullptr )
		{
			m_pcLevelSequencePlayer->Play();
		}
	}
}
