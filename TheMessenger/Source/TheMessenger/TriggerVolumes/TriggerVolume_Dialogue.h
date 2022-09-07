// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerVolume_Base.h"
#include "TheMessenger/Level/Enum_DayTimeType.h"
#include "TriggerVolume_Dialogue.generated.h"

// Forward class declarations (Game)
class ADialogueManager;
class ALevelManager;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API ATriggerVolume_Dialogue : public ATriggerVolume_Base
{
	GENERATED_BODY()
	
private:
	// The dialogue manager needed to initialise the dialogue manager.
	ADialogueManager* m_pcDialogueManager;

	// The level manager needed to set collision when the day time type changes.
	ALevelManager* m_pcLevelManager;

	// The Dialogue ID to initialise the dialogue sequence.
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue IDs" ) )
		FName m_nDialogueIDs;

	// Is this trigger volume, triggerable on day and night
	UPROPERTY( Category = "Properties|Trigger", EditInstanceOnly, meta = ( DisplayName = "Is Triggerable On Time Type" ) )
		bool m_bTriggerableOnTimeType;

	// The day time type to trigger the ambient sound.
	UPROPERTY( Category = "Properties|Trigger", EditInstanceOnly, meta = ( DisplayName = "Trigger At Time Type", EditCondition = "m_bTriggerableOnTimeType" ) )
		EDayTimeType m_eDayToTrigger;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnChangedDay()
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To set the collision based on the time type the level is on.
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
	// Parameters		: All of these parameters are predefined by Unreal Engine 4 for begin overlap event.
	// Purpose			: This is the callback function needed to set "OnBeginOverlap" function in BeginPlay().
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit ) override;
};
