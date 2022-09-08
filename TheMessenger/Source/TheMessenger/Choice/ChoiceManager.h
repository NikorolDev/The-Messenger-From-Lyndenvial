// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_Choice.h"
#include "ChoiceManager.generated.h"

// Forward class Declarations (Engine)
class UBillboardComponent;

// Forward class Declarations (Game)
class ADialogueManager;
class UChoiceSelectionWidget;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AChoiceManager
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor
// Purpose				: This class will hold all the choices and display the correct choices in the selction widget.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API AChoiceManager : public AActor
{
	GENERATED_BODY()
	
private:	
	// Dialogue manager needed to get called when the dialogue is updated when choice is required.
	ADialogueManager* m_pcDialogueManager;

	// The choice selection widget needed to display the choices on the selction widget.
	UChoiceSelectionWidget* m_pcChoiceSelectionWidget;

	// This billboard component will visualise the manager in the map editor.
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Choice Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

	// This is a sub class of the desired widget to be used to display choice selection widget.
	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Choice Selection Widget" ) )
		TSubclassOf<UChoiceSelectionWidget> m_tcChoiceSelectionWidget;

	// This choices table will hold the choices in the level. 
	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Choices" ) )
		TMap<FName, FStructChoiceBranches> m_pfsChoices;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: DisplayChoices( FName ChoiceID )
	// Author			: Nikodem Hamrol
	// Purpose			: When the dialogue finishes and it requires the choices, it passes the choice ID to create choices and 
	//					,	display the hoice selection widget.
	// Parameters		: ChoiceID = the desired choice ID needed to be displayed.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void DisplayChoices( FName ChoiceID );

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To create the choice selection widget for choices and bind display choices to the delegate from dialogue
	//					,	manager.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

public:		
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: AChoiceManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	AChoiceManager();

};
