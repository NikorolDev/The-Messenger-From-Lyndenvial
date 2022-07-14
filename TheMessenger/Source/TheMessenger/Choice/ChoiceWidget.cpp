// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoiceWidget.h"

#include <Components/Button.h>
#include <Components/RichTextBlock.h>

void UChoiceWidget::OnButtonClicked()
{
	// 
	ChoiceSelected.Broadcast( m_iBranchID );
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Green,
		TEXT( "Clicked" ) );
}

void UChoiceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ChoiceButton->OnClicked.AddDynamic( this, &UChoiceWidget::OnButtonClicked );
}

void UChoiceWidget::SetButtonText( int iChoiceCount, const FString& ChoiceDisplayText, FName& rnDialogueID )
{
	m_iBranchID	= iChoiceCount;

	ChoiceText->SetText( FText::FromString( ChoiceDisplayText ) );

	SetVisibility( ESlateVisibility::Visible );
}
