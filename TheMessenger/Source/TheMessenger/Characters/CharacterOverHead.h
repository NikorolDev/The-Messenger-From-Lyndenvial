// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterOverHead.generated.h"

class UOverlay;
class UTextBlock;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API UCharacterOverHead : public UUserWidget
{
	GENERATED_BODY()

private:
	// This will check if the dialogue is already displayed on the screen.
	bool m_bIsDialogueDisplayed;

	bool m_bIsDisplayed;

	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* CharacterName;

	// The rich text block component that will display the text.
	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* DialogueText;

	UPROPERTY( meta = ( BindWidget ) )
		UOverlay* InteractableOverlay;

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
	// Purpose			: 
	// Parameters		: rsDialogueText - The dialogue text that needs to be displayed.
	//-----------------------------------------------------------------------------------------------------------------------------
	void DisplayText( FString& rsDialogueText );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HideDialogue()
	// Author			: Nikodem Hamrol
	// Purpose			: To hide the widget when the dialogue finishes
	//-----------------------------------------------------------------------------------------------------------------------------
	void HideDialogue();

	void ToggleOnFocusOverlayVisibility( bool bIsVisible, bool bIsInteractable = false );

	void SetCharacterName( const FName& pnCharacterName );
};
