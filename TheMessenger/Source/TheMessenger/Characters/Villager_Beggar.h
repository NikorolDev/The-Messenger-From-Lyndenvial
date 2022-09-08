// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Villager_Base.h"
#include "Villager_Beggar.generated.h"

// Forward class declarations (Game)
class ATriggerVolume_Sequence;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AVillager_Beggar
// Author				: Nikodem Hamrol
// Classes Inherited	: AVillager_Base
// Purpose				: This is the beggar class, that is one of the main characters.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API AVillager_Beggar : public AVillager_Base
{
	GENERATED_BODY()

private:
	// If the beggar was helped in level.
	bool m_bhasHelped;

	// The day that the beggar should appear after day 1.
	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "Day To Appear" ) )
		int m_iDayToAppear;

	// The level sequence trigger volume that is can only be triggered on day 4 when the player helps him.
	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "Trigger Volume Assigned" ) )
		ATriggerVolume_Sequence* m_pcTriggerVolumeAssigned;

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: AVillager_Beggar()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	AVillager_Beggar();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnImpactActor_Implementation()
	// Author			: Nikodem Hamrol
	// Purpose			: The impact that beggar will have when initiated, which is appearing on Day 4 and activating the trigger
	//					,	volume.
	//---------------------------------------------------------------------------------------------------------------------------- 
	virtual void OnImpactActor_Implementation() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetHasHelped( bool bHasHelped )
	// Author			: Nikodem Hamrol
	// Purpose			: This is to set if the beggar was helped.
	// Parameters		, bHasHelped - Whether the beggar was helped or not.
	//---------------------------------------------------------------------------------------------------------------------------- 
	UFUNCTION( BlueprintCallable )
		void SetHasHelped( bool bHasHelped );
};
