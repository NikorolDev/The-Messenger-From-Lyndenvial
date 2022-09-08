// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_HintProperties.h"
#include "HintsManager.generated.h"

// Forward class declarations (Engine)
class UBillboardComponent;

// Forward class declarations (Game)
class ADialogueManager;
class ALevelManager;
class UPlayerHUD;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AHintsManager
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor
// Purpose				: This class will hold all the hints, display the current one using the player HUD.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API AHintsManager : public AActor
{
	GENERATED_BODY()
	
private:
	// Whether the hint should be displayed.
	bool m_bHintDisplay;

	// The current hint properties set.
	FHintProperties* m_pfsCurrentHint;

	// The dialogue manager to be used to bind the display hint on dialogue finished.
	ADialogueManager* m_pcDialogueManager;

	// The player hud that will allow for the hint pop ups to display.
	UPlayerHUD* m_pcPlayerHUD;

	// This billboard will visualise the manager in the map editor.
	UPROPERTY( EditDefaultsOnly, meta = ( DisplayName = "Tooltip Manager Display" ) )
		UBillboardComponent* m_pcHintsManagerBillboard;

	// The map container, that holds hint properties.
	UPROPERTY( EditInstanceOnly, meta = ( DisplayName = "Hints" ) )
		TMap<FName, FHintProperties> m_tmHints;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: DisplayHintPopUp()
	// Author			: Nikodem Hamrol
	// Purpose			: To pop up the hint after dialogue finished.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void DisplayHintPopUp();

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: It gets the dialogue manager to pop up hint when dialogue is finished.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

public:	
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: ADialogueManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	AHintsManager();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetHint( FName& rcnObjectiveID )
	// Author			: Nikodem Hamrol
	// Purpose			: To set the hint in the player HUD.
	// Parameters		: rcnObjectiveID - The ID that will get the hint and .
	//---------------------------------------------------------------------------------------------------------------------------- 
	void SetHint( FName& rcnObjectiveID );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetHintDisplay( bool bHintDisplay )
	// Author			: Nikodem Hamrol
	// Purpose			: To set the hint display to be able to pop up.
	// Parameters		: bHintDisplay - Whether the hint is allowed to be displayed
	//----------------------------------------------------------------------------------------------------------------------------
	void SetHintDisplay( bool bHintDisplay );

};
