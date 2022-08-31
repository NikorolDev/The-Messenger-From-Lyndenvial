// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Villager_Base.h"
#include "Villager_StoryGuard.generated.h"

class ALevelSequenceActor;
class ULevelSequencePlayer;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API AVillager_StoryGuard : public AVillager_Base
{
	GENERATED_BODY()

private:
	bool m_bHasSequencePlayed;

	// The sequence player to play the final cutscene.
	ULevelSequencePlayer* m_pcLevelSequencePlayer;

	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue ID After Sequence" ) )
		FName m_nDialogueIDAfterSeqeunce;

	// The sequence actor that is in the level which holds the sequence to play.
	UPROPERTY( Category = "Properties|Interaction Sequence", EditInstanceOnly, meta = ( DisplayName = "Sequence" ) )
		ALevelSequenceActor* m_pcLevelSequenceToPlay;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnDialogueFinished() override;
};
