// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Character.h"

#include <Components/AudioComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Dialogue/DialogueWidgetHUD.h"


// Sets default values
AInteractable_Character::AInteractable_Character()
	: m_bInteracted (false)
	, m_nDialogueID ("")
	, m_bWillFollowPlayer (false)
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

	// Text Render Component (m_pcDialogueTextComponent).
	//m_pcDialogueTextComponent = CreateDefaultSubobject<UTextRenderComponent>( TEXT( "Dialogue Text Render Component" ) );
}

// Called when the game starts or when spawned
void AInteractable_Character::BeginPlay()
{
	Super::BeginPlay();
	
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );
	m_pcDialogueWidget = Cast<UDialogueWidgetHUD>( m_pcWidgetComponent->GetWidget() );

	// Check if the character is allowed to follow the player.
	if( m_bWillFollowPlayer )
	{
		// Bind the function to when the dialogue finishes that will make the character follow the player.
		//m_pcDialogueManager->DialogueFinished.BindUObject( this, &AInteractable_Character::FollowPlayer );
	}
}

// Called every frame
void AInteractable_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable_Character::OnInteract_Implementation( AActor* Caller )
{
	// Retrieve the dialogue sequence that will be played.
	FStructDialogueSequence* CurrentDialogueSequence = &m_pcDialogueManager->GetDialogueSequence( m_nDialogueID );
	FStructDialogueProperties* DialogueSequence = &CurrentDialogueSequence->DialogueSequence[ 0 ];

	// Check if the dialogue sequence will not be played in a level sequencer
	if( !CurrentDialogueSequence->bIsSequenceRequired )
	{
		m_pcDialogueWidget->DisplayText( DialogueSequence->CharacterName, DialogueSequence->DialogueText );
		m_pcAudioComponent->SetSound( DialogueSequence->DialogueAudio );
		//m_pcAudioComponent.Location
	}

	// Initialise the dialogue to play.
	m_pcDialogueManager->InitialiseDialogueSequence( m_nDialogueID );
}

void AInteractable_Character::OnFocus_Implementation()
{
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Green,
		TEXT( "On Focus" ) );
}

void AInteractable_Character::LostFocus_Implementation()
{
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
		TEXT( "Lost Focus" ) );
}
