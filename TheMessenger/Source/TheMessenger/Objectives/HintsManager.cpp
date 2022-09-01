// Fill out your copyright notice in the Description page of Project Settings.


#include "HintsManager.h"

#include <Components/BillboardComponent.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/TheMessengerCharacter.h"
#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Level/LevelManager.h"
#include "TheMessenger/Player/PlayerHUD.h"

// Sets default values
AHintsManager::AHintsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Billboard Component (m_pcHintsManagerBillboard)
	m_pcHintsManagerBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "HintManagerBillboard" ) );
	RootComponent = m_pcHintsManagerBillboard;

}

void AHintsManager::DisplayHintPopUp()
{
	if( m_bHintDisplay )
	{
		UE_LOG( LogTemp, Display, TEXT( "DISPLAYING HINTS" ) );
		m_pcPlayerHUD->DisplayHintPopUp();
	}
}

// Called when the game starts or when spawned
void AHintsManager::BeginPlay()
{
	//
	Super::BeginPlay();

	// Get the player character to get the HUD, to display the objectives.
	//ATheMessengerCharacter* pcPlayer = Cast<ATheMessengerCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 ) );
	//m_pcPlayerHUD = &pcPlayer->GetPlayerHUD();

	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );

	//IntialiseForNewDay();
}

void AHintsManager::IntialiseForNewDay()
{
	m_pcDialogueManager = &m_pcLevelManager->GetCurrentDialogueManager();
	m_pcDialogueManager->DialogueFinished.AddUObject( this, &AHintsManager::DisplayHintPopUp );
}

void AHintsManager::SetHint( FName& rcnObjectiveID )
{
	// Set new objective by finding the objective struct 
	m_pfsCurrentHint = m_tmHints.Find( rcnObjectiveID );

	if( m_pcPlayerHUD == nullptr )
	{
		// Get the player character to get the HUD, to display the objectives.
		ATheMessengerCharacter* pcPlayer = Cast<ATheMessengerCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 ) );
		m_pcPlayerHUD = pcPlayer->GetPlayerHUD();
	}

	// Set Hint UI Elements
	m_pcPlayerHUD->SetHintUIElements( *m_pfsCurrentHint );

	m_bHintDisplay = true;
}

void AHintsManager::SetHintDisplay( bool bHintDisplay ) { m_bHintDisplay = bHintDisplay; }
