// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoiceSelectionWidget.h"

#include <Components/VerticalBox.h>
#include <Kismet/GameplayStatics.h>

#include "ChoiceWidget.h"
#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Interactable/Interactable_Base.h"

void UChoiceSelectionWidget::OnChoiceSelected( const FName& rnDialogueID )
{
	m_pcDialogueManager->InitialiseDialogueSequence( rnDialogueID );
}

void UChoiceSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility( ESlateVisibility::Hidden );
}

void UChoiceSelectionWidget::CreateChoices( FStructChoiceBranches* pfsChoiceBranches )
{
	int iChoiceCount = 1;
	
	for( int iChoiceBranch = 0; iChoiceBranch < pfsChoiceBranches->ChoiceBranches.Num(); ++iChoiceBranch )
	{
		FStructChoiceProperties& ChoiceProperties = pfsChoiceBranches->ChoiceBranches[ iChoiceBranch ];
	
		UChoiceWidget* ChoiceWidget = CreateWidget<UChoiceWidget>( this, m_tcChoiceWidget );
		ChoiceWidget->ChoiceSelected.AddDynamic( this, &UChoiceSelectionWidget::OnChoiceSelected );

		ChoiceWidget->SetButtonText( iChoiceCount, ChoiceProperties.ChoiceDisplayText, ChoiceProperties.DialogueID );
	
		ChoiceBox->AddChildToVerticalBox( ChoiceWidget );
	
		iChoiceCount++;
	}
}

void UChoiceSelectionWidget::SetDialogueManager( ADialogueManager* pcDialogueManager )
{
	m_pcDialogueManager = pcDialogueManager;
}
