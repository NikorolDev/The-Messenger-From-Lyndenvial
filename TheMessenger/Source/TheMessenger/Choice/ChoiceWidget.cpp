// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoiceWidget.h"

#include <Components/Button.h>
#include <Components/RichTextBlock.h>
#include <Styling/SlateColor.h>

void UChoiceWidget::OnButtonClicked()
{
	// Broadcast the choice selected passing the ID of the choice selected.
	ChoiceSelected.Broadcast( m_iBranchID );
}

void UChoiceWidget::NativeConstruct()
{
	// Call the UUserWidget constructor
	Super::NativeConstruct();

	// Bind on button clicked to broadcast the choice selected.
	ChoiceButton->OnClicked.AddDynamic( this, &UChoiceWidget::OnButtonClicked );
}

void UChoiceWidget::SetButtonText( int iChoiceCount, const FString& ChoiceDisplayText )
{
	// Set the button text, by setting the branch ID that will be used to determine what choice has been selected.
	m_iBranchID	= iChoiceCount;

	// Set the text and make the button visible.
	ChoiceText->SetText( FText::FromString( ChoiceDisplayText ) );
	SetVisibility( ESlateVisibility::Visible );
}

void UChoiceWidget::SetTextColour( const FLinearColor& krfsTextColour )
{
	// Set the colour of the text.
	ChoiceText->SetDefaultColorAndOpacity( FSlateColor( krfsTextColour ) );
}
