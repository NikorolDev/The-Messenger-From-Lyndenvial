// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManager.h"

#include <Components/AudioComponent.h>
#include <Components/BillboardComponent.h>
#include <Kismet/GameplayStatics.h>

#include "DialogueWidgetHUD.h"
#include "TheMessenger/Characters/Villager_Base.h"
#include "TheMessenger/Characters/CharacterOverHead.h"

// Sets default values
ADialogueManager::ADialogueManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Billboard Component (m_pcIconBillboard).
	m_pcIconBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "Diaogue Manager Icon" ) );
	RootComponent = m_pcIconBillboard;

	// Audio Component (m_pcAudioComponent).
	m_pcAudioComponent = CreateDefaultSubobject<UAudioComponent>( TEXT( "Audio Component" ) );
	m_pcAudioComponent->SetupAttachment( m_pcIconBillboard );
}

void ADialogueManager::BeginPlay()
{
	// Call the base class's begin play function, which would be from AActor class.
	Super::BeginPlay();
	
	// Create a widget from the subclass of the widget, which should be "BPW_DialogueWidgetHUD". This initialises the private 
	// instance of the widget.
	// Get the player controller as a correct reference to create the widget.
	m_pcDialogueWidgetHUD = CreateWidget<UDialogueWidgetHUD>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), 
																m_tcDialogueWidgetHUD );

	// Check if the dialogue widget hud was successfully created.
	if( m_pcDialogueWidgetHUD )
	{
		// After successful check it will add the dialogue widget to viewport.
		m_pcDialogueWidgetHUD->AddToViewport();
	}
}

void ADialogueManager::InitialiseDialogueSequence( const FName& rnDialogueID )
{
	// Check if there is a dialogue sequence active.
	if( m_pfsDialogueSequence )
	{
		// If so, clear the timer handle as it will not trigger events happening after the dialogue is finished.
		GetWorldTimerManager().ClearTimer( m_fsTimerHandleDialogueDuration );
		//m_pfsDialogueSequence->DialogueSequence
	}

	// Reset the dialogue ID to 0 to get the first dialogue term in the sequence.
	// Reset the dialogue term duration to 0 and find the correct dialogue in the table.
	m_iDialogueID = 0;
	m_fDialogueTermTime = 0.0f;
	m_pfsDialogueSequence = m_tmDialogueTable.Find( rnDialogueID );

	// As the dialogue sequence was found, set the max number of dialogue terms in the sequence to check if the whole sequence
	// is complete.
	m_iNumberOfDialogueTerms = m_pfsDialogueSequence->DialogueSequence.Num();

	// Now set the dialogue term to play it.
	SetDialogueTerm();

}

void ADialogueManager::PlayDialogueTerm()
{
	// Increment the dialogue ID to set the next one in the term.
	m_iDialogueID++;

	// Set the timer, so it will call "SetDialogueTerm" to set the next term.
	GetWorldTimerManager().SetTimer( m_fsTimerHandleDialogueDuration, this, &ADialogueManager::SetDialogueTerm, m_fDialogueTermTime, false );
}

void ADialogueManager::SetDialogueTerm()
{
	// Check if the dialogue ID is less than number of terms in the sequence.
	if( m_iDialogueID < m_iNumberOfDialogueTerms )
	{
		// Create an instance of dialogue properties struct.
		FStructDialogueProperties* dialogueTerm = &m_pfsDialogueSequence->DialogueSequence[ m_iDialogueID ];

		if( dialogueTerm->CharacterToSpeak )
		{
			//m_bIsAmbientDialoguePlaying = true;

			if( m_pcCurrentVillagerSpeaking )
			{
				m_pcCurrentVillagerSpeaking->GetCharatcerOverHead().HideDialogue();
			}

			m_pcCurrentVillagerSpeaking = dialogueTerm->CharacterToSpeak;

			if( dialogueTerm->DialogueAudio )
			{
				m_fDialogueTermTime = dialogueTerm->DialogueAudio->GetDuration();
				dialogueTerm->CharacterToSpeak->PlayAmbientDialogueSequence( dialogueTerm->DialogueText, dialogueTerm->DialogueAudio );
			}
		}
		else
		{
			// Check if the dialogue text is not empty.
			if( !dialogueTerm->DialogueText.IsEmpty() )
			{
				m_pcDialogueWidgetHUD->DisplayText( dialogueTerm->CharacterName, dialogueTerm->DialogueText );
			}

			// Check if the dialogue audio exists.
			if( dialogueTerm->DialogueAudio )
			{
				// Set the dialogue audio duration for closing the dialogue widget before the term duration finishes.
				// Set dialogue term duration, using the duration offset and the duration of the audio file.
				m_fDialogueInitialDuration = dialogueTerm->DialogueAudio->GetDuration();

				// Use the audio component to set the dialogue audio to play and play it.
				// Replaced the use of gameplay statics as the audio component gives more control of the audio being played.
				m_pcAudioComponent->SetSound( dialogueTerm->DialogueAudio );
				m_pcAudioComponent->Play();
			}

			// Set dialogue term duration, using the duration offset and the duration of the audio file or set duration of text display.
			m_fDialogueTermTime = dialogueTerm->DialogueDurationOffset + m_fDialogueInitialDuration;
		}

		// Play the dialogue term.
		PlayDialogueTerm();
	}
	else // If all dialogue terms were played.
	{		
		// Check if the choice is required for this sequence.
		if( m_pfsDialogueSequence->bIsChoiceRequired )
		{
			// Broadcast the event, which will be retrieved by the choice maanger to setup the choice selection window.
			DialogueUpdate.Broadcast(m_pfsDialogueSequence->ChoiceID);
		}
		else // If a choice is not required for this sequence.
		{
			//AVillager_Base* pcVillager = nullptr;
			//
			//if( m_pfsDialogueSequence->DialogueSequence[ m_iDialogueID - 1 ].CharacterToSpeak != nullptr ||
			//	m_pfsDialogueSequence->DialogueSequence[ m_iDialogueID ].CharacterToSpeak != nullptr )
			//{
			//	pcVillager = m_pfsDialogueSequence->DialogueSequence[ m_iDialogueID - 1 ].CharacterToSpeak;
			//}

			// Hide the dialogue widget and now the manager is ready to reintialised next dialogue.
			m_pcDialogueWidgetHUD->HideDialogue();

			//if( pcVillager )
			//{
			//	m_pfsDialogueSequence->DialogueSequence[ m_iDialogueID ].CharacterToSpeak->OnDialogueFinished();
			//}

			DialogueFinished.Broadcast();
		}
	}
}

FStructDialogueSequence& ADialogueManager::GetDialogueSequence( const FName& rnDialogueID )
{
	FStructDialogueSequence* DialogueSequence = m_tmDialogueTable.Find( rnDialogueID );
	return *DialogueSequence;
}
