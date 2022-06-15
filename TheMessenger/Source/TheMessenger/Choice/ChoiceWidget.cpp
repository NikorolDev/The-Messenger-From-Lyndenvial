// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoiceWidget.h"

#include <Components/Button.h>
#include <Components/RichTextBlock.h>

void UChoiceWidget::OnButtonClicked()
{
	ChoiceSelected.Broadcast( *m_pnAssignedChoiceID );
}

void UChoiceWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ChoiceButton->OnClicked.AddDynamic( this, &UChoiceWidget::OnButtonClicked );
}

void UChoiceWidget::SetButtonText( int ChoiceCount, const FString& ChoiceDisplayText, FName& rnDialogueID )
{
	m_pnAssignedChoiceID = &rnDialogueID;

	ChoiceText->SetText( FText::FromString( FString::FromInt( ChoiceCount ) + ". " + ChoiceDisplayText));

}
