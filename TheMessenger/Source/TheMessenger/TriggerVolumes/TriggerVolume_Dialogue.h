// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerVolume_Base.h"
#include "TriggerVolume_Dialogue.generated.h"

class AAmbientDialogueManager;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API ATriggerVolume_Dialogue : public ATriggerVolume_Base
{
	GENERATED_BODY()
	
private:

	AAmbientDialogueManager* m_pcAmbientDialogueManager;

	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue IDs" ) )
		TArray<FName> m_aDialogueIDs;

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
