// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerVolume_Base.h"
#include "TheMessenger/Characters/InfluentiableThroughChoice.h"
#include "TriggerVolume_Blockade.generated.h"

// Forward class Declarations (Game)
class ADialogueManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_Blockade
// Author				: Nikodem Hamrol
// Classes Inherited	: ATriggerVolume_Base
// Purpose				: This class is responsible for blocking the player. 
//----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API ATriggerVolume_Blockade : public ATriggerVolume_Base, public IInfluentiableThroughChoice
{
	GENERATED_BODY()

private:
	// The dialogue manager to play the dialogue.
	ADialogueManager* m_pcDialogueManager;

	// If it is passable when the game starts.
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Is Passable" ) )
		bool m_bIsPassable;

	// The dilaogue ID to initialise.
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue IDs" ) )
		FName m_nDialogueID;
	
protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To add the OnBeginOverlapTrigger callback function when overlapping with the box collider.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnBeginOverlapTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	//					,	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, FHitResult& Hit)
	// Author			: Nikodem Hamrol
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	// Purpose			: This is the callback function needed to set "OnBeginOverlap" function in BeginPlay().
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit ) override;

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: ADialogueManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	ATriggerVolume_Blockade();
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnImpactActor_Implementation()
	// Author			: Nikodem Hamrol
	// Notes			: This will unblock the trigger by disabling the collision.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnImpactActor_Implementation() override;
};
