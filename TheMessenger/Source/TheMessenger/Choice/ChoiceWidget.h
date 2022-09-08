// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct_Choice.h"
#include "ChoiceWidget.generated.h"

// Forward class declarations (Engine)
class UButton;
class URichTextBlock;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FChoiceSelectedSignature, const int, iBranchID );

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UChoiceWidget
// Author				: Nikodem Hamrol
// Classes Inherited	: UUserWidget
// Purpose				: This class will be responsible for a choice selction and making sure they are represented by the
//						,	correct choice.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API UChoiceWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	// The branch ID is choice button identifier from the choice selection widget.
	int m_iBranchID;

	// The button that will be used for the choice to be selected.
	UPROPERTY( meta = ( BindWidget ) )
		UButton* ChoiceButton;

	// The choice text that is on the button.
	UPROPERTY( meta = ( BindWidget ) )
		URichTextBlock* ChoiceText;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnButtonClicked()
	// Author			: Nikodem Hamrol
	// Purpose			: This function is the delegate, which is called when the button is clicked. It will broadcast the event
	//					,	which is set in the ChoiceSelectionWidget.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OnButtonClicked();

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: This is the constructor to the widget, which is similar to the "Event Construct" in Blueprint Widget.
	//					,	It is used to setup the on button clicked delegate function call.
	//-----------------------------------------------------------------------------------------------------------------------------
		virtual void NativeConstruct() override;

public:
	// The choice selected signature that is used to broadcast to the selection widget.
	UPROPERTY( BlueprintAssignable, BlueprintCallable )
		FChoiceSelectedSignature ChoiceSelected;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetButtonText( int iChoiceCount, const FString& ChoiceDisplayText )
	// Author			: Nikodem Hamrol
	// Purpose			: Sets the button text and the representation of the choice by a number.
	// Parameters		: iChoiceCount - The representation of the from when the choice was displayed.
	//					, ChoiceDisplayText - The text to display choice.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetButtonText( int iChoiceCount, const FString& ChoiceDisplayText );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetTextColour( const FLinearColor& krfsTextColour )
	// Author			: Nikodem Hamrol
	// Purpose			: Sets the button text colour.
	// Parameters		: krfsTextColour - The desired colour of the button text.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetTextColour( const FLinearColor& krfsTextColour );
};
