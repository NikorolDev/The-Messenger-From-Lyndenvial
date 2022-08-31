// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_Base.h"

#include <Components/AudioComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

#include "CharacterOverHead.h"
#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/TheMessengerCharacter.h"

// Sets default values
AVillager_Base::AVillager_Base()
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


// Called when the game starts or when spawned
void AVillager_Base::BeginPlay()
{
	Super::BeginPlay();

	// Get the ambient dialogue manager from the level.
	Initialise();

	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );
	m_pcDialogueManager->DialogueFinished.AddUObject( this, &AVillager_Base::OnDialogueFinished );

	m_pcPlayer = Cast<ATheMessengerCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 ) );

	// Get the character over head widget.
	//m_pcCharacterOverHead = Cast<UCharacterOverHead>( m_pcWidgetComponent->GetWidget() );	
}

void AVillager_Base::OnInteract_Implementation( AActor* Caller )
{
	if( m_bIsInteractable )
	{
		FStructDialogueSequence* CurrentDialogueSequence = &m_pcDialogueManager->GetDialogueSequence( m_nDialogueID );
		
		if( CurrentDialogueSequence->bIsASequence )
		{
			m_bIsInSequence = true;
			//LostFocus_Implementation();
			m_bInteracted = true;

			FVector PlayerPosition = GetActorLocation() + ( GetActorForwardVector() * m_fPlayerDistanceInSequence );
			float PlayerRotationYaw = GetActorRotation().Yaw + 180;
		
			m_pcPlayer->SetPlayerForSequence( PlayerPosition, PlayerRotationYaw );
		}

		m_pcDialogueManager->InitialiseDialogueSequence( m_nDialogueID );
	}
}

void AVillager_Base::OnFocus_Implementation()
{
	if( !m_bIsInSequence )
	{
		m_pcCharacterOverHead->ToggleOnFocusOverlayVisibility( true, m_bIsInteractable );
	}
	//else
	//{
	//	LostFocus_Implementation();
	//}
}

void AVillager_Base::LostFocus_Implementation()
{
	m_pcCharacterOverHead->ToggleOnFocusOverlayVisibility( false );
}

void AVillager_Base::OnImpactDialogue_Implementation( const FName& krnDialogueID )
{
	m_nDialogueID = krnDialogueID;
}

void AVillager_Base::Initialise()
{
	// Get the character over head widget.
	m_pcCharacterOverHead = Cast<UCharacterOverHead>( m_pcWidgetComponent->GetWidget() );

	m_pcCharacterOverHead->SetCharacterName( m_nCharacterName );
}

void AVillager_Base::OnDialogueFinished()
{
	m_pcCharacterOverHead->HideDialogue();
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

void AVillager_Base::SetInteracted( bool bInteracted )
{
	m_bInteracted = bInteracted;
}

const bool AVillager_Base::GetInteracted() const
{
	return m_bInteracted;
}

void AVillager_Base::SetIsInSequence( bool bIsInSequence )			{ m_bIsInSequence = bIsInSequence; }

const bool AVillager_Base::GetIsInteractable() const				{ return m_bIsInteractable; }

void AVillager_Base::SetDialogueID( const FName& krnDialogueID )	{ m_nDialogueID = krnDialogueID; }

FName& AVillager_Base::GetDialogueID()								{ return m_nDialogueID; }

ADialogueManager& AVillager_Base::GetDialogueManager() const		{ return *m_pcDialogueManager; }

ATheMessengerCharacter& AVillager_Base::GetPlayer() const
{
	return *m_pcPlayer;
}

UCharacterOverHead& AVillager_Base::GetCharatcerOverHead() const	{ return *m_pcCharacterOverHead; }
