// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidgetHUD.generated.h"

// Forward class declaration
class URichTextBlock;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UDialogueWidgetHUD
// Author				: Nikodem Hamrol
// Classes Inherited	: UUserWidget
// Purpose				: This class will be responsible to display the dialogue text onto the screen. As well as 
//						,	appearing when the dialogue sequence starts and hiding when the sequence finishes
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API UDialogueWidgetHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	// This will check if the dialogue is already displayed on the screen.
	bool m_bIsDialogueDisplayed;

	// the rich text block that will display the character's name.
	UPROPERTY( meta = ( BindWidget ) )
		URichTextBlock* CharacterNameText;

	// The rich text block component that will display the dialogue text.
	UPROPERTY( meta = ( BindWidget ) )
		URichTextBlock* DialogueText;

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
	// Function Name	: DisplayText( FString& rsCharacterName, FString& rsDialogueText )
	// Author			: Nikodem Hamrol
	// Purpose			: To set the widget to visible when the dialogue sequence starts and 
	//					,	display the text that is passed from the dialogue manager onto the screen.
	// Parameters		: rsCharacterName	- The name of the character that speaks.
	//					, rsDialogueText	- The dialogue text that needs to be displayed.
	//-----------------------------------------------------------------------------------------------------------------------------
	void DisplayText( FString& psCharacterName, FString& rsDialogueText );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HideDialogue()
	// Author			: Nikodem Hamrol
	// Purpose			: To hide the widget when the dialogue finishes
	//-----------------------------------------------------------------------------------------------------------------------------
	void HideDialogue();
};
