// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_StoryGuard.h"

#include <LevelSequence/Public/LevelSequenceActor.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>

#include "CharacterOverHead.h"
#include "TheMessenger/Dialogue/DialogueManager.h"

void AVillager_StoryGuard::BeginPlay()
{
	// Call the base class begin play.
	AVillager_Base::BeginPlay();

	// Create default sequence playback settings.
	FMovieSceneSequencePlaybackSettings m_pfsLevelSequencePlaybackSettings;

	// If the level sequencer is not a nullptr set the sequencer player to the level sequencer set.
	if( m_pcLevelSequenceToPlay != nullptr )
	{
		m_pcLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer( GetWorld(), m_pcLevelSequenceToPlay->GetSequence(), m_pfsLevelSequencePlaybackSettings, m_pcLevelSequenceToPlay );
	}

	// Bind to dialogue finished delegate.
	GetDialogueManager().DialogueFinished.AddUObject( this, &AVillager_StoryGuard::OnDialogueFinished );
}

void AVillager_StoryGuard::OnDialogueFinished()
{
	// Check if it was interacted.
	if( GetInteracted() )
	{
		// If sequence has not played.
		if( !m_bHasSequencePlayed )
		{
			// Play the level sequencer.
			m_bHasSequencePlayed = true;
			m_pcLevelSequencePlayer->Play();
		}
	}

	// Call the base on dialogue finished.
	AVillager_Base::OnDialogueFinished();
}
