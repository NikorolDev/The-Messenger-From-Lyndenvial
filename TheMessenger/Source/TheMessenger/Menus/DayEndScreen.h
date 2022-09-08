// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DayEndScreen.generated.h"

class UButton;
class UTextBlock;

class AEndingManager;
class ALevelManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UDayEndScreen
// Author				: Nikodem Hamrol
// Classes Inherited	: UUserWidget
// Purpose				: This class will be responsible for the transition between ending interaction with Lord Sigismund and 
//						,	the next day or the endings
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API UDayEndScreen : public UUserWidget
{
	GENERATED_BODY()

private:
	// The ending manager needed to play the cinematic.
	AEndingManager* m_pcEndingManager;

	// The level manager needed to set the new day.
	ALevelManager* m_pcLevelManager;

	// The main menu button to get back to the main menu.
	UPROPERTY( meta = ( BindWidget ) )
		UButton* MainMenu;
	 
	// The continue button to set the next days.
	UPROPERTY( meta = ( BindWidget ) )
		UButton* Continue;

	// Day complete text display.
	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* DayComplete;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnContinueClicked()
	// Author			: Nikodem Hamrol
	// Purpose			: On continue clicked button, to set the next day.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OnContinueClicked();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnMainMenuClicked()
	// Author			: Nikodem Hamrol
	// Purpose			: On main menu button to take the player to the main menu.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OnMainMenuClicked();

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
	// Function Name	: DisplayScreen()
	// Author			: Nikodem Hamrol
	// Purpose			: This will be display screen if there is no endings to be triggered.
	//-----------------------------------------------------------------------------------------------------------------------------
	void DisplayScreen();	
};
