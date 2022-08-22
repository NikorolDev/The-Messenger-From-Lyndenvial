// Fill out your copyright notice in the Description page of Project Settings.


#include "AmbientDialogueManager.h"

#include <Components/BillboardComponent.h>

#include "TheMessenger/Characters/Villager_Base.h"
#include "TheMessenger/Characters/CharacterOverHead.h"

// Sets default values
AAmbientDialogueManager::AAmbientDialogueManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Billboard Component (m_pcIconBillboard).
	m_pcIconBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "Diaogue Manager Icon" ) );
	RootComponent = m_pcIconBillboard;
}

// Called when the game starts or when spawned
void AAmbientDialogueManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAmbientDialogueManager::PlayDialogueTerm()
{
	// Increment the dialogue ID to set the next one in the term.
	m_iDialogueID++;

	// Create a timer handle struct , which will be used to set the timer.
	//FTimerHandle fsTimerHandleDialogueDuration;
	FTimerHandle fsTimerHandle1;

	// Set the timer, so it will hide the diaogue widget when dialogue audio finishes.
	//GetWorldTimerManager().SetTimer( fsTimerHandleDialogueDuration, m_pcDialogueWidgetHUD, &UDialogueWidgetHUD::HideDialogue, m_fDialogueInitialDuration, false);

	// Set the timer, so it will call "SetDialogueTerm" to set the next term.
	GetWorldTimerManager().SetTimer( fsTimerHandle1, this, &AAmbientDialogueManager::SetDialogueTerm, m_fDialogueTermTime, false );
}

void AAmbientDialogueManager::SetDialogueTerm()
{
	if( m_iDialogueID < m_iNumberOfDialogueTerms )
	{
		FAmbientDialogueProperties* fsAmbientDialogueTerm = &m_pfsDialogueSequence->AmbientDialogueSequence[ m_iDialogueID ];

		if( fsAmbientDialogueTerm->CharacterToSpeak )
		{
			if( m_pcCurrentVillagerSpeaking )
			{
				m_pcCurrentVillagerSpeaking->GetCharatcerOverHead().HideDialogue();
			}
			
			m_pcCurrentVillagerSpeaking = fsAmbientDialogueTerm->CharacterToSpeak;


			if( fsAmbientDialogueTerm->DialogueAudio )
			{
				m_fDialogueTermTime = fsAmbientDialogueTerm->DialogueAudio->GetDuration();
				fsAmbientDialogueTerm->CharacterToSpeak->PlayAmbientDialogueSequence( fsAmbientDialogueTerm->DialogueText, 
																						fsAmbientDialogueTerm->DialogueAudio );
			}

			PlayDialogueTerm();
		}
	}
	else
	{
		m_bIsDialogueSequenceInitialised = false;
		m_pcCurrentVillagerSpeaking->GetCharatcerOverHead().HideDialogue();
		m_pcCurrentVillagerSpeaking = nullptr;
	}
}

void AAmbientDialogueManager::InitialiseDialogueSequence( const FName& rnDialogueID )
{
	if( !m_bIsDialogueSequenceInitialised )
	{
		m_iDialogueID = 0;
		m_fDialogueTermTime = 0;
		m_pfsDialogueSequence = m_tmAmbientDialogueTable.Find( rnDialogueID );

		if( m_pfsDialogueSequence )
		{
			m_bIsDialogueSequenceInitialised = true;

			m_iNumberOfDialogueTerms = m_pfsDialogueSequence->AmbientDialogueSequence.Num();

			SetDialogueTerm();
		}
	}
}
