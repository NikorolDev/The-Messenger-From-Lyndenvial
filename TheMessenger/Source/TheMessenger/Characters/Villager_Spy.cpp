// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_Spy.h"

#include <LevelSequence/Public/LevelSequenceActor.h>
#include <LevelSequence/Public/LevelSequencePlayer.h>

#include "CharacterOverHead.h"
#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Level/LevelManager.h"

void AVillager_Spy::BeginPlay()
{
	AVillager_Base::BeginPlay();

	if( m_iDayToAppear != 0 )
	{
		HideCharacter( true );
	}

	// Create default sequence playback settings.
	FMovieSceneSequencePlaybackSettings m_pfsLevelSequencePlaybackSettings;

	if( m_pcLevelSequenceToPlay != nullptr )
	{
		m_pcLevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer( GetWorld(), m_pcLevelSequenceToPlay->GetSequence(), m_pfsLevelSequencePlaybackSettings, m_pcLevelSequenceToPlay );
	}

	GetDialogueManager().DialogueFinished.AddUObject( this, &AVillager_Spy::OnDialogueFinished );
	GetLevelManager().OnChangedDay.AddUObject( this, &AVillager_Spy::AppearOnThisDay );
}

void AVillager_Spy::AppearOnThisDay()
{
	if( GetLevelManager().GetDayID() == m_iDayToAppear )
	{
		HideCharacter( false );
	}
}

void AVillager_Spy::OnDialogueFinished()
{
	GetCharatcerOverHead().HideDialogue();

	if( GetInteracted() )
	{
		if( !m_bHasSequencePlayed && m_pcLevelSequenceToPlay != nullptr )
		{
			m_bHasSequencePlayed = true;
			m_pcLevelSequencePlayer->Play();
		}
	}
}

void AVillager_Spy::OnImpactActor_Implementation()
{
	HideCharacter( true );
}
