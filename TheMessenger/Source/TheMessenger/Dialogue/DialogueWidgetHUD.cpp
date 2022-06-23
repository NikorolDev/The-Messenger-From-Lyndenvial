// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueWidgetHUD.h"

#include <Components/RichTextBlock.h>

void UDialogueWidgetHUD::NativeConstruct()
{
	// Call the native construct from the UUserWidget.
	Super::NativeConstruct();

	// Hide the dialogue widget so it is not visible when the player starts the game.
	HideDialogue();

	UE_LOG( LogTemp, Display, TEXT( "[UDialogueWidgetHUD::NativeConstruct L.15] DIALOGUE WIDGET CONSTRUCTED" ) );
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

		UE_LOG( LogTemp, Display, TEXT( "[UDialogueWidgetHUD::DisplayText L.28] DIALOGUE WIDGET IS NOW VISIBLE" ) );
	}

	//if( rsCharacterName.IsEmpty() )
	//{
	//	DialogueText->SetText( FText::FromString( rsDialogueText ) );
	//}
	//else
	//{
	//	// Set the text of the dialogue with the character name.
	//	// Concatenate the text so the character name can be manipulated via "DT_WidgetTextData", which holds how text should look like.
	//}
		DialogueText->SetText( FText::FromString( "<Character>" + rsCharacterName + "</> " + rsDialogueText ) );

	UE_LOG( LogTemp, Display, TEXT( "[UDialogueWidgetHUD::DisplayText L.34] NEW DIALOGUE TEXT DISPLAYED" ) );
}

void UDialogueWidgetHUD::HideDialogue()
{
	// Set visibility of the dialogue to be hidden and set the boolean to be false, so it can be redisplayed.
	SetVisibility( ESlateVisibility::Hidden );
	m_bIsDialogueDisplayed = false;

	UE_LOG( LogTemp, Display, TEXT( "[UDialogueWidgetHUD::HideDialogue L.43] DIALOGUE WIDGET IS NOW HIDDEN" ) );
}
