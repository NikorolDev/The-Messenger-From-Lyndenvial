// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueWidgetHUD.h"

#include <Components/RichTextBlock.h>

void UDialogueWidgetHUD::NativeConstruct()
{
	// Call the native construct from the UUserWidget.
	Super::NativeConstruct();

	// Hide the dialogue widget so it is not visible when the player starts the game.
	HideDialogue();
}

void UDialogueWidgetHUD::DisplayText( FString& rsCharacterName, FString& rsDialogueText )
{
	// Check if this widget is not displayed.
	if( !m_bIsDialogueDisplayed )
	{
		// Set the dialogue text to be visible and the bool to be true so this code does not get called when the 
		// dialogue sequence is still playing.
		SetVisibility( ESlateVisibility::Visible );
		m_bIsDialogueDisplayed = true;
	}

	// Display character's name and dialogue text.
	CharacterNameText->SetText( FText::FromString( "<Character>" + rsCharacterName + "</>" ) );
	//DialogueText->SetText( FText::FromString( "<Character>" + rsCharacterName + "</> " + rsDialogueText ) );
	DialogueText->SetText( FText::FromString( rsDialogueText ) );
}

void UDialogueWidgetHUD::HideDialogue()
{
	// Set visibility of the dialogue to be hidden and set the boolean to be false, so it can be redisplayed.
	SetVisibility( ESlateVisibility::Hidden );
	m_bIsDialogueDisplayed = false;
}
