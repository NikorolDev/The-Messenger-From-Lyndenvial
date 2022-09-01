// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_StoryGuard.h"

#include <LevelSequence/Public/LevelSequenceActor.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>

#include "CharacterOverHead.h"

void AVillager_StoryGuard::BeginPlay()
{
	AVillager_Base::BeginPlay();

	// Create default sequence playback settings.
	FMovieSceneSequencePlaybackSettings m_pfsLevelSequencePlaybackSettings;

	if( m_pcLevelSequenceToPlay != nullptr )
	{
		m_pcLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer( GetWorld(), m_pcLevelSequenceToPlay->GetSequence(), m_pfsLevelSequencePlaybackSettings, m_pcLevelSequenceToPlay );
	}
}

void AVillager_StoryGuard::OnDialogueFinished()
{
	GetCharatcerOverHead().HideDialogue();

	if( GetInteracted() )
	{
		if( !m_bHasSequencePlayed )
		{
			m_bHasSequencePlayed = true;
			SetDialogueID( m_nDialogueIDAfterSeqeunce );
			m_pcLevelSequencePlayer->Play();
		}
	}
}
