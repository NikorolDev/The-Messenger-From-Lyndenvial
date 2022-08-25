// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_Interactable.h"

#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Dialogue/AmbientDialogueManager.h"
#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Dialogue/Struct_DialogueSequence.h"

void AVillager_Interactable::BeginPlay()
{
	AVillager_Base::BeginPlay();

	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );

	//Initialise();
}

void AVillager_Interactable::OnInteract_Implementation( AActor* Caller )
{
	if( GetIsInteractable() )
	{
		FName* nDialogueID = &GetDialogueID();

		if( m_bIsAmbientDialogue )
		{
			GetAmbientDialogueManager().InitialiseDialogueSequence( *nDialogueID );
		}
		else
		{
			FStructDialogueSequence* CurrentDialogueSequence = &m_pcDialogueManager->GetDialogueSequence( *nDialogueID );

			m_pcDialogueManager->InitialiseDialogueSequence( *nDialogueID );
			
			//if( CurrentDialogueSequence->bIsChoiceRequired )
			//{
			//
			//}
			//else
			//{
			//}


			//m_pcDialogueManager.Initi

		}
	}

	//m_bIsInteractable
	
	
	
	
	//if( m_bCanBeInteracted )
	//{
	//	// Retrieve the dialogue sequence that will be played.
	//	FStructDialogueSequence* CurrentDialogueSequence = &m_pcDialogueManager->GetDialogueSequence( m_nDialogueID );
	//	FStructDialogueProperties* DialogueSequence = &CurrentDialogueSequence->DialogueSequence[ 0 ];
	//
	//	// Check if the dialogue sequence will not be played in a level sequencer
	//	if( CurrentDialogueSequence->bIsSequenceRequired )
	//	{
	//		FVector PlayerPosition = GetActorLocation() + ( GetActorForwardVector() * m_fPlayerDistancePositionInSequence );
	//		float PlayerRotationYaw = GetActorRotation().Yaw + 180;
	//
	//		m_pcPlayer->SetPlayerForSequence( PlayerPosition, PlayerRotationYaw );
	//		m_pcDialogueManager->InitialiseDialogueSequence( m_nDialogueID );
	//	}
	//	else
	//	{
	//		FTimerHandle TimerForDialogue;
	//
	//		m_pcDialogueWidget->DisplayText( DialogueSequence->CharacterName, DialogueSequence->DialogueText );
	//
	//		GetWorldTimerManager().SetTimer( TimerForDialogue, this, &AInteractable_Character::HideOverHeadDialogueWidget,
	//			DialogueSequence->DialogueDurationOffset, false );
	//	}
	//}
}
