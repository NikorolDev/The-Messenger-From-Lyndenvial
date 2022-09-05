// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Villager_Base.h"
#include "Villager_Spy.generated.h"

class ALevelSequenceActor;
class ULevelSequencePlayer;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API AVillager_Spy : public AVillager_Base
{
	GENERATED_BODY()

private:
	bool m_bHasSequencePlayed;

	// The sequence player to play the final cutscene.
	ULevelSequencePlayer* m_pcLevelSequencePlayer;

	// The sequence actor that is in the level which holds the sequence to play.
	UPROPERTY( Category = "Properties|Interaction Sequence", EditInstanceOnly, meta = ( DisplayName = "Sequence" ) )
		ALevelSequenceActor* m_pcLevelSequenceToPlay;

	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "Day To Appear" ) )
		int m_iDayToAppear;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void AppearOnThisDay() override;

public:
	virtual void OnDialogueFinished() override;

	virtual void OnImpactActor_Implementation() override;
	
};
