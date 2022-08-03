// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct_Choice.h"
#include "ChoiceWidget.generated.h"

class UButton;
class URichTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FChoiceSelectedSignature, const int, iBranchID );

/**
 * 
 */
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
	// The choice selected signature that is used to 
	UPROPERTY( BlueprintAssignable, BlueprintCallable )
		FChoiceSelectedSignature ChoiceSelected;

	void SetButtonText( int iChoiceCount, const FString& ChoiceDisplayText, FName& rnDialogueID );

	void SetTextColour( const FLinearColor& krfsTextColour );
};
