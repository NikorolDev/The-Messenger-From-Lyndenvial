// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerVolume_Base.h"
#include "TheMessenger/Characters/InfluentiableThroughChoice.h"
#include "TriggerVolume_Sequence.generated.h"

// Forward class declarations (Engine)
class ALevelSequenceActor;
class ULevelSequencePlayer;

// Forward class declarations (Game)
class AVillager_Base;
class ALevelManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ATriggerVolume_Sequence
// Author				: Nikodem Hamrol
// Classes Inherited	: ATriggerVolume_Base , IInfluentiableThroughChoice
// Purpose				: This class is responsible for triggering level sequences.
//----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API ATriggerVolume_Sequence : public ATriggerVolume_Base, public IInfluentiableThroughChoice
{
	GENERATED_BODY()
	
private:
	// Level manager needed to match the days with the day to trigger.
	ALevelManager* m_pcLevelManager;

	// The sequence player to play the final cutscene.
	ULevelSequencePlayer* m_pcLevelSequencePlayer;

	// Should it trigger on a day number
	UPROPERTY( Category = "Properties|Interaction Sequence", EditInstanceOnly, meta = ( DisplayName = "Trigger On Specified Day" ) )
		bool m_bTriggerOnDay;

	// The desired day that this level sequencer should trigger.
	UPROPERTY( Category = "Properties|Interaction Sequence", EditInstanceOnly, meta = ( DisplayName = "Day To Trigger", EditCondition = "m_bTriggerOnDay" ) )
		int m_iDayToTrigger;

	// The sequence actor that is in the level which holds the sequence to play.
	UPROPERTY( Category = "Properties|Interaction Sequence", EditInstanceOnly, meta = ( DisplayName = "Sequence" ))
		ALevelSequenceActor* m_pcLevelSequenceToPlay;

	// If required, which villager should the level sequencer interact with as soon as the player hits the trigger volume.
	UPROPERTY( Category = "Properties|Interaction Sequence", EditInstanceOnly, meta = ( DisplayName = "Character To Interact" ) )
		AVillager_Base* m_pcVillagerToInteract;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnChangedDay()
	// Author			: Nikodem Hamrol
	// Purpose			: When the day changes it check if they can be triggered on the day.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void OnChangedDay();

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
	// Purpose			: This is the callback function needed to set "OnBeginOverlap" function in BeginPlay().
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnChangedDay()
	// Author			: Nikodem Hamrol
	// Purpose			: On impact actor from choice it wil set collisio to query only.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnImpactActor_Implementation() override;
};
