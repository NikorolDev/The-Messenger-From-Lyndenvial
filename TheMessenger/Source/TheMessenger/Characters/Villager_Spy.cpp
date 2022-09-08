// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_Spy.h"

#include <LevelSequence/Public/LevelSequenceActor.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>

#include "CharacterOverHead.h"
#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Level/LevelManager.h"

void AVillager_Spy::BeginPlay()
{
	// Call the base class begin play.
	AVillager_Base::BeginPlay();

	// If the Spy is not appearring at day 1, hide the character.
	if( m_iDayToAppear != 0 )
	{
		HideCharacter( true );
	}

	// Create default sequence playback settings.
	FMovieSceneSequencePlaybackSettings m_pfsLevelSequencePlaybackSettings;

	// If the level sequencer is not a nullptr set the sequencer player to the level sequencer set.
	if( m_pcLevelSequenceToPlay != nullptr )
	{
		m_pcLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer( GetWorld(), m_pcLevelSequenceToPlay->GetSequence(), m_pfsLevelSequencePlaybackSettings, m_pcLevelSequenceToPlay );
	}

	// Bind the functions to when the dialogue finishes and when it changes day.
	GetDialogueManager().DialogueFinished.AddUObject( this, &AVillager_Spy::OnDialogueFinished );
	GetLevelManager().OnChangedDay.AddUObject( this, &AVillager_Spy::AppearOnThisDay );
}

void AVillager_Spy::AppearOnThisDay()
{
	// Get the day id from the level manager and if it is equal to day to appear.
	if( GetLevelManager().GetDayID() == m_iDayToAppear )
	{
		// Unhide the spy.
		HideCharacter( false );
	}
}

void AVillager_Spy::OnDialogueFinished()
{
	// Has the spy been interacted.
	if( GetInteracted() )
	{
		// Check if the level sequencer has played and if it has been set.
		if( !m_bHasSequencePlayed && m_pcLevelSequenceToPlay != nullptr )
		{
			// Play the level sequence.
			m_bHasSequencePlayed = true;
			m_pcLevelSequencePlayer->Play();
		}
	}

	// Call the base on dialogue finished.
	AVillager_Base::OnDialogueFinished();
}

void AVillager_Spy::OnImpactActor_Implementation()
{
	// Hide the spy.
	HideCharacter( true );
}
