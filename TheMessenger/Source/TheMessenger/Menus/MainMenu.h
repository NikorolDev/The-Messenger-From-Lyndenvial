// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheMessenger/Endings/Struct_CinematicProperties.h"
#include "MainMenu.generated.h"

// Forward class declarations (Engine)
class UButton;
class UMaterialInstance;
class UMediaPlayer;

// Forward class declarations (Game)
class UCinematic;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UMainMenu
// Author				: Nikodem Hamrol
// Classes Inherited	: UUserWidget
// Purpose				: This class will be responsible to navigate around the menus and start game.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:
	// The cinematic widget to play the intro cutscene.
	UCinematic* m_pcCinematicWidget;

	// Cinematic properties containing the intro porperties.
	UPROPERTY( Category = "Properties", EditAnywhere, meta = ( DisplayName = "Intro Cinematic" ) )
		FCinematicProperties m_pfsIntroCinematic;

	// This is a sub class of the desired widget to be used to display dialogue.
	UPROPERTY( Category = "Properties|Widget", EditDefaultsOnly, meta = ( DisplayName = "Cinematic Widget" ) )
		TSubclassOf<UCinematic> m_tcCinematicWidget;

	// This button will play the cinematic intro and load the main game map.
	UPROPERTY( meta = ( BindWidget ) )
		UButton* NewGameButton;

	// This buttone will quit the game.
	UPROPERTY( meta = ( BindWidget ) )
		UButton* QuitButton;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NewGameButtonClicked()
	// Author			: Nikodem Hamrol
	// Purpose			: When button clicked will start playing the cinematic intro and load the main map.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void NewGameButtonClicked();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NewGameButtonClicked()
	// Author			: Nikodem Hamrol
	// Purpose			: When button clicked the game will quit.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void QuitButtonClicked();

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: This is the constructor to the widget, which is similar to the "Event Construct" in Blueprint Widget.
	//					,	It creates the cinematic to play the intro and bind buttons to functions.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;
};
