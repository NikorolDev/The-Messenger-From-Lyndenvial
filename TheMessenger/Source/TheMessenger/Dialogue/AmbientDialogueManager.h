// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_AmbientDialogueProperties.h"
#include "AmbientDialogueManager.generated.h"

// Forward class Declarations (Engine)
class UBillboardComponent;

// Forward class Declarations (Game)
class AInteractable_Character;

UCLASS()
class THEMESSENGER_API AAmbientDialogueManager : public AActor
{
	GENERATED_BODY()

private:
	// To check if the dialogue sequence has been initialised.
	bool m_bIsDialogueSequenceInitialised;

	// The term time for the dialogue, which is calculated with the audio length and the desired delay.
	float m_fDialogueTermTime;

	// The initial duration of dialogue, which is set by.
	float m_fDialogueInitialDuration;

	// The current ID of the dialogue term.
	int m_iDialogueID;

	// The maximum of dialogue terms in a sequence.
	int m_iNumberOfDialogueTerms;

	// An instance of the dialogue.
	FAmbientDialogueSequence* m_pfsDialogueSequence;

	// This billboard component will visualise the manager in the map editor.
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Ambient Dialgoue Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

	// This dialogue table will hold the dialogue in the level
	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Ambient Dialogue Table" ) )
		TMap<FName, FAmbientDialogueSequence> m_tmDialogueTable;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetDialogueTerm()
	// Author			: Nikodem Hamrol
	// Purpose			: To set the dialogue term to be played. To also check if dialogue audio is included and dialogue text.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetDialogueTerm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AAmbientDialogueManager();

	void InitialiseDialogueSequence( const FName& rnDialogueID );
};
