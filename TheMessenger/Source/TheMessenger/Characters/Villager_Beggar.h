// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Villager_Base.h"
#include "Villager_Beggar.generated.h"


class ATriggerVolume_Sequence;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API AVillager_Beggar : public AVillager_Base
{
	GENERATED_BODY()

private:

	bool m_bhasHelped;

	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "Day To Appear" ) )
		int m_iDayToAppear;

	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "Trigger Volume Assigned" ) )
		ATriggerVolume_Sequence* m_pcTriggerVolumeAssigned;

protected:
	virtual void BeginPlay() override;

public:
	AVillager_Beggar();

	virtual void OnImpactActor_Implementation() override;

	UFUNCTION( BlueprintCallable )
		void SetHasHelped( bool bHasHelped );

	//virtual void OnImpactDialogue_Implementation( const FName& krnDialogueID ) override;
};
