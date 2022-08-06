// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoiceSelectionWidget.h"

#include <Components/VerticalBox.h>
#include <Kismet/GameplayStatics.h>

#include "ChoiceWidget.h"
#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Interactable/Interactable_Character.h"
#include "TheMessenger/Objectives/HintsManager.h"

void UChoiceSelectionWidget::OnChoiceSelected( int iBranchID )
{
	SetVisibility( ESlateVisibility::Hidden );
	m_pcPlayerController->bShowMouseCursor = false;

	// Create a temporary struct of the impact from the choice chosen. This is to minimise the search in the array.
	FStructChoiceProperties* ChoiceSelected = &m_pfsChoices->ChoiceBranches[ iBranchID ];

	// Set the input mode to be game only
	//m_pcPlayerController->SetInputMode( FInputModeGameOnly() );

	// When a choice is selected hide the window and initialise next dialogue.
	//SetVisibility( ESlateVisibility::Hidden );
	m_pcDialogueManager->InitialiseDialogueSequence( ChoiceSelected->DialogueID );

	m_pcHintsManager->SetHint( ChoiceSelected->ChoiceImpactProperties.HintID );

	// Check if the character affected is not nullptr to properly set the impact 
	if( ChoiceSelected->ChoiceImpactProperties.CharacterAffected != nullptr )
	{
		// Set the new dialogue ID for the affected character.
		//m_pcBranchManager->SetNewDialogueID( &ChoiceSelected->ChoiceImpactProperties );
		ChoiceSelected->ChoiceImpactProperties.CharacterAffected->SetDialogueID( ChoiceSelected->ChoiceImpactProperties.NewDialogueID );
	}
}

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

	//m_pcBranchManager = Cast<ABranchManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ABranchManager::StaticClass() ) );

	m_pcHintsManager		= Cast<AHintsManager>( UGameplayStatics::GetActorOfClass( GetWorld(), AHintsManager::StaticClass() ) );
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

		m_aChoiceWidgets[iChoiceBranch]->SetButtonText(iChoiceBranch, ChoiceProperties.ChoiceDisplayText, ChoiceProperties.DialogueID);

		switch( ChoiceProperties.eChoiceType )
		{
			case EChoiceType::Hidden:
			{
				m_aChoiceWidgets[ iChoiceBranch ]->SetVisibility( ESlateVisibility::Collapsed );
				break;
			}

			case EChoiceType::Main:
			{
				m_aChoiceWidgets[ iChoiceBranch ]->SetTextColour( m_afsChoiceTextColours[ 0 ] );
				break;
			}

			case EChoiceType::Optional:
			case EChoiceType::Exit:
			{
				m_aChoiceWidgets[ iChoiceBranch ]->SetTextColour( m_afsChoiceTextColours[ 1 ] );
				break;
			}
		}
	
		//DEPRECATED
		//UChoiceWidget* ChoiceWidget = CreateWidget<UChoiceWidget>( this, m_tcChoiceWidget );
		//ChoiceWidget->ChoiceSelected.AddDynamic( this, &UChoiceSelectionWidget::OnChoiceSelected );
	
		// Set the selection.
		
		//DEPRECATED
		//m_aChoiceWidgets[iChoiceBranch]
		//ChoiceBox->AddChildToVerticalBox( ChoiceWidget );
	}

	// When all buttons are set. Toggle mouse cursor visibility and set game input to UI only.
	//m_pcPlayerController->SetInputMode( FInputModeUIOnly() );
	m_pcPlayerController->bShowMouseCursor = true;
}

void UChoiceSelectionWidget::SetDialogueManager( ADialogueManager* pcDialogueManager ) { m_pcDialogueManager = pcDialogueManager; }
