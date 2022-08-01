// Fill out your copyright notice in the Description page of Project Settings.


#include "HintsManager.h"

#include <Components/BillboardComponent.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/TheMessengerCharacter.h"
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

// Called when the game starts or when spawned
void AHintsManager::BeginPlay()
{
	//
	Super::BeginPlay();

	// Get the player character to get the HUD, to display the objectives.
	ATheMessengerCharacter* pcPlayer = Cast<ATheMessengerCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 ) );
	m_pcPlayerHUD = &pcPlayer->GetPlayerHUD();

		
}

// Called every frame
void AHintsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHintsManager::SetObjective( FName& rcnObjectiveID )
{
	// Set new objective by finding the objective struct 
	m_pfsCurrentHint = m_tmHints.Find( rcnObjectiveID );

	//m_pcPlayerHUD.Set
}
