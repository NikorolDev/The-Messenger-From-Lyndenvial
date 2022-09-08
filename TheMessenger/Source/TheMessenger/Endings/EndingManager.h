// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_CinematicProperties.h"
#include "EndingManager.generated.h"

// Forward class Declarations (Engine)
class UBillboardComponent;

// Forward class Declarations (Game)
class ALevelManager;
class UCinematic;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AEndingManager
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor
// Purpose				: This class will hold all the endings and play the correct ending.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API AEndingManager : public AActor
{
	GENERATED_BODY()
	
private:
	// The ending that got triggered.
	FCinematicProperties* m_pfsEndingTriggered;

	// The level manager to check if the day ID matches the day to trigger the ending.
	ALevelManager* m_pcLevelManager;

	// Cinematic widget where the ending gets displayed.
	UCinematic* m_pcCinematicWidget;

	// The endings map containing the properties to play a specific ending.
	UPROPERTY( Category = "Properties|Endings Sequence", EditInstanceOnly, meta = ( DisplayName = "Endings" ) )
		TMap<FName, FCinematicProperties> m_tmEndings;

	// This is a sub class of the desired widget to be used to play the cinematic.
	UPROPERTY( Category = "Properties|Endings Sequence", EditInstanceOnly, meta = ( DisplayName = "Cinematic Widget" ) )
		TSubclassOf<UCinematic> m_tcCinematicWidget;

	// This billboard component will visualise the manager in the map editor.
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Ending Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To create the cinematic widget get the level manager.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

public:	
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: AEndingManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	AEndingManager();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: DisplayEnding()
	// Author			: Nikodem Hamrol
	// Purpose			: To check if it can display the ending instead of the day end screen.
	// Returns			: boolean to say if it can display ending or not.
	//----------------------------------------------------------------------------------------------------------------------------
	const bool DisplayEnding();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: TriggerEnding( const FName& krnEndingID )
	// Author			: Nikodem Hamrol
	// Purpose			: To set the ending to be triggered
	// Parameters		: The ending ID to get the ending from the map container.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( BlueprintCallable )
		void TriggerEnding( const FName& krnEndingID );
};
