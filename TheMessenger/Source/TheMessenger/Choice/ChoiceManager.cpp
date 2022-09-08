// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoiceManager.h"

#include <Components/BillboardComponent.h>
#include <Kismet/GameplayStatics.h>

#include "ChoiceSelectionWidget.h"
#include "TheMessenger/Dialogue/DialogueManager.h"

// Sets default values
AChoiceManager::AChoiceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Billboard Component (m_pcIconBillboard).
	m_pcIconBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "Diaogue Manager Icon" ) );
	RootComponent = m_pcIconBillboard;
}

void AChoiceManager::BeginPlay()
{
	// Call the Actor's begin play to initialise it in the level.
	Super::BeginPlay();
	
	// Get the dialogue manager from the level and bind dialogue update delegate to display choices.
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );
	m_pcDialogueManager->DialogueUpdate.AddDynamic( this, &AChoiceManager::DisplayChoices );

	// Create the choice selection widget. Set the managers to the widget being this one the dialogue manager and add it to viewport.
	m_pcChoiceSelectionWidget = CreateWidget<UChoiceSelectionWidget>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), m_tcChoiceSelectionWidget );
	m_pcChoiceSelectionWidget->SetDialogueManager( m_pcDialogueManager );
	m_pcChoiceSelectionWidget->AddToViewport(1);
}

void AChoiceManager::DisplayChoices(FName ChoiceID)
{	
	// Display the choices and set visibility of the choice selection widget.
	m_pcChoiceSelectionWidget->CreateChoices( m_pfsChoices.Find( ChoiceID ) );
	m_pcChoiceSelectionWidget->SetVisibility( ESlateVisibility::Visible );
}
