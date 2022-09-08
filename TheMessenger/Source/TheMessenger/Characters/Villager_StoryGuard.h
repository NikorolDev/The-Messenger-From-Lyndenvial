// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Villager_Base.h"
#include "Villager_StoryGuard.generated.h"

// Forward class Declarations (Engine)
class ALevelSequenceActor;
class ULevelSequencePlayer;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AVillager_Spy
// Author				: Nikodem Hamrol
// Classes Inherited	: AVillager_Base
// Purpose				: This is the spy class, that is one of the main characters.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API AVillager_StoryGuard : public AVillager_Base
{
	GENERATED_BODY()

private:
	// Whether the sequence has already been played.
	bool m_bHasSequencePlayed;

	// The sequence player to play the final cutscene.
	ULevelSequencePlayer* m_pcLevelSequencePlayer;

	// The sequence actor that is in the level which holds the sequence to play.
	UPROPERTY( Category = "Properties|Interaction Sequence", EditInstanceOnly, meta = ( DisplayName = "Sequence" ) )
		ALevelSequenceActor* m_pcLevelSequenceToPlay;


protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To set a level sequence player and bind functions to impact actor and dialogue finished.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnDialogueFinished()
	// Author			: Nikodem Hamrol
	// Purpose			: To play the level sequencer when the dialogue finishes.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnDialogueFinished() override;
};
