// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterOverHead.h"

#include <Components/Overlay.h>
#include <Components/TextBlock.h>

void UCharacterOverHead::NativeConstruct()
{
	// Call the native construct from the UUserWidget.
	Super::NativeConstruct();

	// Hide the dialogue and the on focus overlay.
	ToggleOnFocusOverlayVisibility( false );
	HideDialogue();
}

void UCharacterOverHead::DisplayText( FString& rsDialogueText )
{
	// Check if the dialogue is not displayed.
	if( !m_bIsDialogueDisplayed )
	{
		// Set the visibility of the dialogue text.
		DialogueText->SetVisibility( ESlateVisibility::Visible );
		m_bIsDialogueDisplayed = true;
	}

	// Set the text of the dialogue.
	DialogueText->SetText( FText::FromString( rsDialogueText ) );
}

void UCharacterOverHead::HideDialogue()
{
	// Hide the dialogue text.
	DialogueText->SetVisibility( ESlateVisibility::Hidden );
	m_bIsDialogueDisplayed = false;
}

void UCharacterOverHead::ToggleOnFocusOverlayVisibility( bool bIsVisible, bool bIsInteractable )
{
	// Check if the character overhead should be visible
	if( bIsVisible )
	{
		// Set on focus overlay to visible.
		OnFocusOverlay->SetVisibility( ESlateVisibility::Visible );

		// If it is an interactable villager.
		if( bIsInteractable )
		{
			// Then set visibility of the interactable overlay/
			InteractableOverlay->SetVisibility( ESlateVisibility::Visible );
		}
	}
	else
	{
		// Otherwise, hide all of the overlays.
		InteractableOverlay->SetVisibility( ESlateVisibility::Hidden );
		OnFocusOverlay->SetVisibility( ESlateVisibility::Hidden );
	}
}

void UCharacterOverHead::SetCharacterName( const FName& pnCharacterName )
{
	// Set the character name to be seen in the overhead.
	CharacterName->SetText( FText::FromString( pnCharacterName.ToString() ) );
}
