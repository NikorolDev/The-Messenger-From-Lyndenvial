// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterOverHead.generated.h"

// Forward class declarations (Engine)
class UOverlay;
class UTextBlock;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ADialogueManager
// Author				: Nikodem Hamrol
// Classes Inherited	: UUserWidget
// Purpose				: This class display the dialogue, the charcter name and overlays over the character's head.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API UCharacterOverHead : public UUserWidget
{
	GENERATED_BODY()

private:
	// This will check if the dialogue is already displayed on the screen.
	bool m_bIsDialogueDisplayed;

	// The character name of the villager that this widget is attached to.
	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* CharacterName;

	// The rich text block component that will display the text.
	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* DialogueText;

	// Interactable overlay showing the button to interact and interaction type.
	UPROPERTY( meta = ( BindWidget ) )
		UOverlay* InteractableOverlay;

	// The focus overlay to show the character's name only.
	UPROPERTY( meta = ( BindWidget ) )
		UOverlay* OnFocusOverlay;

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: This is the constructor to the widget, which is similar to the "Event Construct" in Blueprint Widget.
	//					,	It is used to hide itself when starting the game.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: DisplayText( FString& rsDialogueText )
	// Author			: Nikodem Hamrol
	// Purpose			: To display the dialogue text that is passed from the villager.
	// Parameters		: rsDialogueText - The dialogue text that needs to be displayed.
	//-----------------------------------------------------------------------------------------------------------------------------
	void DisplayText( FString& rsDialogueText );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HideDialogue()
	// Author			: Nikodem Hamrol
	// Purpose			: To hide the dialogue text when it is finished
	//-----------------------------------------------------------------------------------------------------------------------------
	void HideDialogue();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ToggleOnFocusOverlayVisibility( bool bIsVisible, bool bIsInteractable = false )
	// Author			: Nikodem Hamrol
	// Purpose			: To toggle on and off the overlays that are focus from the villager.
	// Parameters		: bIsVisible		- To display the focus overlay.
	//					, bIsInteractable	- To display the interactable overlay.
	//-----------------------------------------------------------------------------------------------------------------------------
	void ToggleOnFocusOverlayVisibility( bool bIsVisible, bool bIsInteractable = false );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HideDialogue()
	// Author			: Nikodem Hamrol
	// Purpose			: To set the character name to represent the villager.
	// Parameters		: pnCharacterName - The desired character name.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetCharacterName( const FName& pnCharacterName );
};
