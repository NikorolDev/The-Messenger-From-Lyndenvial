// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingManager.h"

#include <Components/BillboardComponent.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Level/LevelManager.h"
#include "TheMessenger/Menus/Cinematic.h"

// Sets default values
AEndingManager::AEndingManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Billboard Component (m_pcIconBillboard).
	m_pcIconBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "Diaogue Manager Icon" ) );
	RootComponent = m_pcIconBillboard;
}

void AEndingManager::BeginPlay()
{
	// Call the Actor's begin play.
	Super::BeginPlay();
	
	// Create a widget from the subclass of the widget, which should be "BPW_Cinematic". This initialises the private 
	// instance of the widget.
	// Get the player controller as a correct reference to create the widget.
	m_pcCinematicWidget = CreateWidget<UCinematic>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), 
																m_tcCinematicWidget );
	m_pcCinematicWidget->AddToViewport();
	m_pcCinematicWidget->SetAccessedFromMainMenu( false );

	// Get the level manager that is active in the level.
	m_pcLevelManager = Cast<ALevelManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ALevelManager::StaticClass() ) );

	// Set a dummy ending to check for ending trigger. This specific ending will only get triggered at the end of the game.
	// This allows the check to get the Day ID.
	m_pfsEndingTriggered = m_tmEndings.Find( "Loyalty" );
}

const bool AEndingManager::DisplayEnding()
{
	// If the current day is the same as the day to trigger the ending
	if( m_pfsEndingTriggered->DayToTrigger == m_pcLevelManager->GetDayID() )
	{
		// Play the cinematic, passing the ending properties.
		m_pcCinematicWidget->PlayCinematic( *m_pfsEndingTriggered );
		return true;
	}
	return false;
}

void AEndingManager::TriggerEnding( const FName& krnEndingID )
{
	// Find the ending properties based on the ending ID.
	m_pfsEndingTriggered = m_tmEndings.Find( krnEndingID );
}
