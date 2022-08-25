// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterOverHead.h"

#include <Components/Overlay.h>
#include <Components/TextBlock.h>

void UCharacterOverHead::NativeConstruct()
{
	Super::NativeConstruct();

	ToggleOnFocusOverlayVisibility( false );
	HideDialogue();
}

void UCharacterOverHead::DisplayText( FString& rsDialogueText )
{
	if( !m_bIsDialogueDisplayed )
	{
		DialogueText->SetVisibility( ESlateVisibility::Visible );
		m_bIsDialogueDisplayed;
	}

	DialogueText->SetText( FText::FromString( rsDialogueText ) );
}

void UCharacterOverHead::HideDialogue()
{
	DialogueText->SetVisibility( ESlateVisibility::Hidden );
	m_bIsDialogueDisplayed = false;
}

void UCharacterOverHead::ToggleOnFocusOverlayVisibility( bool bIsVisible, bool bIsInteractable )
{
	if( bIsVisible )
	{
		OnFocusOverlay->SetVisibility( ESlateVisibility::Visible );

		if( bIsInteractable )
		{
			InteractableOverlay->SetVisibility( ESlateVisibility::Visible );
		}
	}
	else
	{
		InteractableOverlay->SetVisibility( ESlateVisibility::Hidden );
		OnFocusOverlay->SetVisibility( ESlateVisibility::Hidden );
	}
}

void UCharacterOverHead::SetCharacterName( const FName& pnCharacterName )
{
	CharacterName->SetText( FText::FromString( pnCharacterName.ToString() ) );
}
