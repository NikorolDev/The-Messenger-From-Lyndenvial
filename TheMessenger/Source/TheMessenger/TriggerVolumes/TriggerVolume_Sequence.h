// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerVolume_Base.h"
#include "TriggerVolume_Sequence.generated.h"

class ALevelSequenceActor;
class ULevelSequencePlayer;

class AVillager_Base;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API ATriggerVolume_Sequence : public ATriggerVolume_Base
{
	GENERATED_BODY()
	
private:

	// The sequence player to play the final cutscene.
	ULevelSequencePlayer* m_pcLevelSequencePlayer;

	// The sequence actor that is in the level which holds the sequence to play.
	UPROPERTY( Category = "Properties|Interaction Sequence", EditInstanceOnly, meta = ( DisplayName = "Sequence" ))
		ALevelSequenceActor* m_pcLevelSequenceToPlay;

	UPROPERTY( Category = "Properties|Interaction Sequence", EditInstanceOnly, meta = ( DisplayName = "Character To Interact" ) )
		AVillager_Base* m_pcInteractedCharacter;

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
};
