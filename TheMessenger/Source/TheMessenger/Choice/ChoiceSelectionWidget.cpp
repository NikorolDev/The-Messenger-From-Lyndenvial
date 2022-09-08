// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoiceSelectionWidget.h"

#include <Components/VerticalBox.h>
#include <Kismet/GameplayStatics.h>

#include "ChoiceWidget.h"
#include "TheMessenger/Characters/Villager_Base.h"
#include "TheMessenger/Characters/InfluentiableThroughChoice.h"
#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Endings/EndingManager.h"
#include "TheMessenger/Objectives/HintsManager.h"


void UChoiceSelectionWidget::NativeConstruct()
{
	// Call the native construct from the UUserWidget.
	Super::NativeConstruct();

	// Initialise the array to have 5 choice widgets ready.
	m_aChoiceWidgets.Init( nullptr, 5 );

	// Loop through the max amount choices there will be
	for( int i = 0; i < m_aChoiceWidgets.Num(); ++i )
	{
		// Create the choice widget that will use the BPW version of the widget, set the delegate function to be called when a choice
		// has been selected. Collapse the widget so it won't be seen and add it to the vertical box. 
		m_aChoiceWidgets[ i ] = CreateWidget<UChoiceWidget>( this, m_tcChoiceWidget );
		m_aChoiceWidgets[ i ]->ChoiceSelected.AddDynamic( this, &UChoiceSelectionWidget::OnChoiceSelected );
		m_aChoiceWidgets[ i ]->SetVisibility( ESlateVisibility::Collapsed );
		ChoiceBox->AddChildToVerticalBox( m_aChoiceWidgets[ i ] );
	}

	// Get the Ending manager to set an ending. Get the hints manager to display the hint after dialogue finishes.
	m_pcEndingManager		= Cast<AEndingManager>( UGameplayStatics::GetActorOfClass( GetWorld(), AEndingManager::StaticClass() ) );
	m_pcHintsManager		= Cast<AHintsManager>( UGameplayStatics::GetActorOfClass( GetWorld(), AHintsManager::StaticClass() ) );

	// Get the player controller to set the input mode when selecting choices.
	m_pcPlayerController	= UGameplayStatics::GetPlayerController( GetWorld(), 0 );

	// Hide the widget as no choice scenario is active.
	SetVisibility( ESlateVisibility::Hidden );
}

void UChoiceSelectionWidget::CreateChoices( FStructChoiceBranches* pfsChoiceBranches )
{
	// Set the choice branches for this current choice selection scenario
	m_pfsChoices = pfsChoiceBranches;
	
	// Loop through all choice selections in this scenario
	for( int iChoiceBranch = 0; iChoiceBranch < m_pfsChoices->ChoiceBranches.Num(); ++iChoiceBranch )
	{
		// Create a temporary choice properties struct to be set for each selection
		FStructChoiceProperties& ChoiceProperties = m_pfsChoices->ChoiceBranches[ iChoiceBranch ];

		// Set the button text, by passing the choice it represents and the choice text.
		m_aChoiceWidgets[ iChoiceBranch ]->SetButtonText( iChoiceBranch, ChoiceProperties.ChoiceDisplayText );

		// Switch based on the choice type.
		switch( ChoiceProperties.eChoiceType )
		{
			// When choice is hidden.
			case EChoiceType::Hidden:
			{
				// Collapse the choice.
				m_aChoiceWidgets[ iChoiceBranch ]->SetVisibility( ESlateVisibility::Collapsed );
				break;
			}

			// On main choice
			case EChoiceType::Main:
			{
				// Set colour of the text.
				m_aChoiceWidgets[ iChoiceBranch ]->SetTextColour( m_afsChoiceTextColours[ 0 ] );
				break;
			}

			// On optional and exit choices
			case EChoiceType::Optional:
			case EChoiceType::Exit:
			{
				// Set colour of the text.
				m_aChoiceWidgets[ iChoiceBranch ]->SetTextColour( m_afsChoiceTextColours[ 1 ] );
				break;
			}
		}
	}

	// When all buttons are set. Toggle mouse cursor visibility and set game input to UI only.
	m_pcPlayerController->SetInputMode( FInputModeUIOnly() );
	m_pcPlayerController->bShowMouseCursor = true;
}

void UChoiceSelectionWidget::OnChoiceSelected( int iBranchID )
{
	// Hide the widget and set input mode to game only to hide the mouse cursor.
	SetVisibility( ESlateVisibility::Hidden );
	m_pcPlayerController->SetInputMode( FInputModeGameOnly() );
	m_pcPlayerController->bShowMouseCursor = false;

	// Create a temporary struct of the impact from the choice chosen. This is to minimise the search in the array.
	FStructChoiceProperties* ChoiceSelected = &m_pfsChoices->ChoiceBranches[ iBranchID ];

	// Initialise the dialogue.
	m_pcDialogueManager->InitialiseDialogueSequence( ChoiceSelected->DialogueID );

	// Get the number of actors that got impacted.
	int iImpactedActors = ChoiceSelected->ChoiceImpactProperties.Num();

	// Check if there's more than one actor impacted.
	if( iImpactedActors > 0 )
	{
		// Loop through all impacted actors.
		for( int iImpactedActorID = 0; iImpactedActorID < iImpactedActors; ++iImpactedActorID )
		{
			// Get impact properties form the choice selected that is currently in the loop.
			FChoiceImpactProperties* impactProperties = &ChoiceSelected->ChoiceImpactProperties[ iImpactedActorID ];

			// Check if there are any characters influenced.
			if( impactProperties->ChoiceInfluencedCharacter )
			{
				// Impact the dialogue, which will set to a new dialogue.
				impactProperties->ChoiceInfluencedCharacter->OnImpactDialogue_Implementation( impactProperties->NewDialogueID );
			}

			// Check if there are any any actors influenced
			if( impactProperties->ChoiceInfluencedActor )
			{
				// Using the influentiable through choice interface execute on imapct actor. Get the object of the actor to do the execution.
				IInfluentiableThroughChoice::Execute_OnImpactActor( impactProperties->ChoiceInfluencedActor.GetObject() );
			}
		}
	}

	// If there is a hint ID set.
	if( !ChoiceSelected->HintID.IsNone() )
	{
		// Set hint passing throught the hint ID.
		m_pcHintsManager->SetHint( ChoiceSelected->HintID );
	}

	// If the choice triggers an ending. Trigger the ending specified and apps the ID of that ending.
	if( ChoiceSelected->TriggerEnding )
	{
		m_pcEndingManager->TriggerEnding( ChoiceSelected->EndingID );
	}

	// Loop through all the choice widget and collapse them so no previous choices show up.
	for( int iChoiceBranch = 0; iChoiceBranch < m_aChoiceWidgets.Num(); ++iChoiceBranch )
	{
		m_aChoiceWidgets[ iChoiceBranch ]->SetVisibility( ESlateVisibility::Collapsed );
	}
}

void UChoiceSelectionWidget::SetDialogueManager( ADialogueManager* pcDialogueManager )	{ m_pcDialogueManager = pcDialogueManager; }
