// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_Base.h"

#include <Components/AudioComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

#include "CharacterOverHead.h"
#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Level/LevelManager.h"
#include "TheMessenger/TheMessengerCharacter.h"

// Sets default values
AVillager_Base::AVillager_Base()
	: m_bIsActive (true)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Audio Component (m_pcAudioComponent).
	m_pcAudioComponent = CreateDefaultSubobject<UAudioComponent>( TEXT( "Audio Component" ) );
	m_pcAudioComponent->SetupAttachment( GetCapsuleComponent() );

	// Widget Component (m_pcWidgetComponent).
	m_pcWidgetComponent = CreateDefaultSubobject<UWidgetComponent>( TEXT( "Widget Component" ) );
	m_pcWidgetComponent->SetupAttachment( GetCapsuleComponent() );
}

void AVillager_Base::BeginPlay()
{
	// Call the Actor's begin play to initialise it in the level.
	Super::BeginPlay();

	// Check if the widget component has a set widget.
	if( m_pcWidgetComponent->GetWidget() != nullptr )
	{
		// Get the character over head widget and set the character name.
		m_pcCharacterOverHead = Cast<UCharacterOverHead>( m_pcWidgetComponent->GetWidget() );
		m_pcCharacterOverHead->SetCharacterName( m_nCharacterName );
	}

	// Get the dialogue manager from the level and bind a function on when a dialogue is finished.
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );
	m_pcDialogueManager->DialogueFinished.AddUObject( this, &AVillager_Base::OnDialogueFinished );

	// Get the level manager from the level.
	m_pcLevelManager = Cast<ALevelManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ALevelManager::StaticClass() ) );

	// Get the player from the level.
	m_pcPlayer = Cast<ATheMessengerCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 ) );
}

void AVillager_Base::OnInteract_Implementation( AActor* Caller )
{
	// Check if the villager is active.
	if( m_bIsActive )
	{
		// Check if it can be interacted.
		if( m_bIsInteractable )
		{
			// Get the dialogue sequence using the dialogue ID set on the villager.
			FStructDialogueSequence* CurrentDialogueSequence = &m_pcDialogueManager->GetDialogueSequence( m_nDialogueID );

			// Check if the dialogue sequence is a sequential one.
			if( CurrentDialogueSequence->bIsASequence )
			{
				// Set that the villager is interacted and is in sequence with the player
				m_bIsInSequence = true;
				m_bInteracted = true;

				// Turn off the character over head, so it does to show the widget in sequence.
				LostFocus_Implementation();

				// Calculate the position of the player in the sequence.
				// First using the distance in sequence multiply it by the forward of the character, so the player is ahead of the villager.
				// Next get the rotation for the player to face the villager.
				FVector PlayerPosition = GetActorLocation() + ( GetActorForwardVector() * m_fPlayerDistanceInSequence );
				float PlayerRotationYaw = GetActorRotation().Yaw + 180;

				// Set the player fot the sequence.
				m_pcPlayer->SetPlayerForSequence( PlayerPosition, PlayerRotationYaw );
			}

			// Initialise the dialogue, this supports ambient dialogue and sequence dialouge.
			m_pcDialogueManager->InitialiseDialogueSequence( m_nDialogueID );
		}
	}
}

void AVillager_Base::OnFocus_Implementation()
{
	// Check if the player is active and has a character over head
	if( m_bIsActive && m_pcCharacterOverHead )
	{
		// Check if they are not in a sequence.
		if( !m_bIsInSequence )
		{
			// Toggle on the visibility of the character over head and ,use the interactable villager to show the control for interaction.
			m_pcCharacterOverHead->ToggleOnFocusOverlayVisibility( true, m_bIsInteractable );
		}
		else
		{
			// Otherwise, turn off the widget over head.
			LostFocus_Implementation();
		}
	}
}

void AVillager_Base::LostFocus_Implementation()
{
	// If the character over head was initialised.
	if( m_pcCharacterOverHead )
	{
		// Turn off the the widget over head.
		m_pcCharacterOverHead->ToggleOnFocusOverlayVisibility( false );
	}
}

void AVillager_Base::OnImpactDialogue_Implementation( const FName& krnDialogueID )
{
	// Set the dialogue when a villager is impacted by dialogue.
	m_nDialogueID = krnDialogueID;
}

void AVillager_Base::OnDialogueFinished()
{
	// Check if the character over head was initialised
	if( m_pcCharacterOverHead )
	{
		// Hide the dialogue.
		m_pcCharacterOverHead->HideDialogue();
	}

	// The villager is no longer interacted or in a sequence.
	m_bIsInSequence = false;
	m_bInteracted = false;
}

void AVillager_Base::PlayAmbientDialogueSequence( FString& krsDialogueText, USoundWave* pcDialogueAudio )
{
	// Check if the audio has been set from the ambient dialogue manager.
	if( pcDialogueAudio )
	{
		// Set the sound and play it. With attenuation on, it play the sound at location.
		m_pcAudioComponent->SetSound( pcDialogueAudio );
		m_pcAudioComponent->Play();
	}

	// Display the dialogue over head of the character.
	m_pcCharacterOverHead->DisplayText( krsDialogueText );
}

void AVillager_Base::HideCharacter( bool bHideCharacter )
{
	// Check if the character should not be hidden.
	if( !bHideCharacter )
	{
		// Set the character to be active, unhide and set thier collision.
		m_bIsActive = true;
		SetActorHiddenInGame( false );
		GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
	}
	else
	{
		// Otherwise disable the character and collision and hide it.
		m_bIsActive = false;
		SetActorHiddenInGame( true );
		GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	}
}

void AVillager_Base::HideCharacter( EDayTimeType eDayTimeType )
{
	// Check if the character should be hidden away in the game.
	if( !m_bHiddenInGame )
	{
		// Switch based on the time type.
		switch( eDayTimeType )
		{
			// On day time.
			case EDayTimeType::Day:
			{
				// Set the character to be active, unhide and set thier collision.
				m_bIsActive = true;
				SetActorHiddenInGame( false );
				GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::QueryAndPhysics );
				break;
			}
			// On night time.
			case EDayTimeType::Night:
			{
				// Otherwise disable the character and collision and hide it.
				m_bIsActive = false;
				SetActorHiddenInGame( true );
				GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
				break;
			}
		}
	}
}

const bool AVillager_Base::GetActive() const						{ return m_bIsActive; }

void AVillager_Base::SetInteracted( bool bInteracted )				{ m_bInteracted = bInteracted; }

const bool AVillager_Base::GetInteracted() const					{ return m_bInteracted; }

const bool AVillager_Base::GetActiveAtNight() const					{ return m_bActiveAtNight; }

void AVillager_Base::SetIsInSequence( bool bIsInSequence )			{ m_bIsInSequence = bIsInSequence; }

const bool AVillager_Base::GetIsInteractable() const				{ return m_bIsInteractable; }

void AVillager_Base::SetDialogueID( const FName& krnDialogueID )	{ m_nDialogueID = krnDialogueID; }

FName& AVillager_Base::GetDialogueID()								{ return m_nDialogueID; }

ADialogueManager& AVillager_Base::GetDialogueManager() const		{ return *m_pcDialogueManager; }

ALevelManager& AVillager_Base::GetLevelManager() const				{ return *m_pcLevelManager; }

ATheMessengerCharacter& AVillager_Base::GetPlayer() const			{ return *m_pcPlayer; }

UCharacterOverHead& AVillager_Base::GetCharatcerOverHead() const	{ return *m_pcCharacterOverHead; }
