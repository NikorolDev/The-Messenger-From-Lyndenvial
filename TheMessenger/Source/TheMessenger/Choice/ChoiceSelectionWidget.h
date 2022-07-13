// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct_Choice.h"
#include "ChoiceSelectionWidget.generated.h"

// Forward class declarations (Engine)
class UChoiceWidget;
class UVerticalBox;

// Forward class declarations (Game)
class ABranchManager;
class ADialogueManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UChoiceSelectionWidget
// Author				: Nikodem Hamrol
// Classes Inherited	: UUserWidget
// Purpose				: This class will be responsible to display the choices on to the screen. It will set the choices,
//						,	set the impact of the choice made and continue the dialogue.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API UChoiceSelectionWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	ABranchManager*			m_pcBranchManager;

	// The dialogue manager needed to continue the dialogue after the choice was made.
	ADialogueManager*		m_pcDialogueManager;

	// The choice selection struct of the current choices that will be displayed.
	FStructChoiceBranches*	m_pfsChoices;

	// An array of the choice widgets that will be used.
	TArray<UChoiceWidget*>	m_aChoiceWidgets;

	// The vertical box that the choices will be placed.
	UPROPERTY( meta = ( BindWidget ) )
		UVerticalBox* ChoiceBox;
	
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnChoiceSelected( int iBranchID, const FName& rnDialogueID )
	// Author			: Nikodem Hamrol
	// Purpose			: This delegate function will be called when a choice is selected and it will play a continued dialogue and
	//					,	set the impact of the choice if there is any.
	// Parameters		: iBranchID	- The choice that was selected which is identified from the element number of m_aChoiceWidgets.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OnChoiceSelected( int iBranchID );

protected:

	// The widget that will be used to display the choices.
	UPROPERTY( Category = Widgets, EditDefaultsOnly, BlueprintReadOnly )
		TSubclassOf<UChoiceWidget> m_tcChoiceWidget;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: This is the constructor to the widget, which is similar to the "Event Construct" in Blueprint Widget.
	//					,	It is used to create an array choice widgets and hide the menu until a choice scenario is active.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: CreateChoices( FStructChoiceBranches* pfsChoiceBranches )
	// Author			: Nikodem Hamrol
	// Purpose			: This function will create choices based on the choice ID that was set in the choice manager.
	//-----------------------------------------------------------------------------------------------------------------------------
	void CreateChoices( FStructChoiceBranches* pfsChoiceBranches );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetDialogueManager(ADialogueManager* pcDialogueManager)
	// Author			: Nikodem Hamrol
	// Purpose			: This function will set the dialogue manager to be used to play the dialogue after a choice is selected.
	// Parameters		: pcDialogueManager	- The dialogue manager that is currently in use for the current day.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetDialogueManager(ADialogueManager* pcDialogueManager);
};
