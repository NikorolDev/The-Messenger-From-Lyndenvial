// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheMessenger/Endings/Struct_CinematicProperties.h"
#include "Cinematic.generated.h"

// Forward class declarations (Engine)
class UImage;
class UMaterialInstance;
class UMediaPlayer;
class UTextBlock;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UCinematic
// Author				: Nikodem Hamrol
// Classes Inherited	: UUserWidget
// Purpose				: This class will play the cinematics, either the intro or ending.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API UCinematic : public UUserWidget
{
	GENERATED_BODY()

private:
	// Whether it is accessed from main menu to load the correct map. 
	UPROPERTY( Category = "Properties", EditDefaultsOnly, BlueprintReadOnly, meta = ( DisplayName = "Accessed From Main Menu", AllowPrivateAccess = true ) )
		bool m_bAccessedFromMainMenu;

	// The skip text display.
	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* SkipText;

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: This is the constructor to the widget, which is similar to the "Event Construct" in Blueprint Widget.
	//					,	It is used to hide itself when starting the game.
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

	// The image that the cinematic will play from.
	UPROPERTY( BlueprintReadOnly, meta = ( BindWidget ) )
		UImage* CinematicImage;

public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: PlayCinematic( FCinematicProperties pfsEndingProperties )
	// Author			: Nikodem Hamrol
	// Purpose			: To play the cinematic.
	// Parameters		: pfsEndingProperties - The cinematic properties needed to set the cinematic and play it.
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void PlayCinematic( FCinematicProperties pfsEndingProperties );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetAccessedFromMainMenu( bool bAccessedFromMainMenu )
	// Author			: Nikodem Hamrol
	// Purpose			: Set accessed from main menu so the correct map can load.
	// Parameters		: bAccessedFromMainMenu - Whether it was accessed from the main menu or not.
	//-----------------------------------------------------------------------------------------------------------------------------
	void SetAccessedFromMainMenu( bool bAccessedFromMainMenu );
};
