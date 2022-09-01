// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_DialogueSequence.h"
#include "DialogueManager.generated.h"

// Forward class Declarations (Engine)
class UAudioComponent;
class UBillboardComponent;

// Forward class Declarations (Game)
class AVillager_Base;
class UDialogueWidgetHUD;

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDialogueUpdatedSignature, FName, Name );
DECLARE_MULTICAST_DELEGATE( FDialogueFinished );

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ADialogueManager
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor
// Purpose				: This class will hold all the dialogue and display the correct sequence onto the widget within a 
//						,	level.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API ADialogueManager : public AActor
{
	GENERATED_BODY()
	
private:
#pragma region Private Variables (not exposed to the editor)
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
	FStructDialogueSequence* m_pfsDialogueSequence;

	// The current villager that is speaking through ambient dialogue.
	AVillager_Base* m_pcCurrentVillagerSpeaking;

	// The dialogue widget that will display dialogue for the manager.
	UDialogueWidgetHUD* m_pcDialogueWidgetHUD;

#pragma endregion

#pragma region Private Variables (exposed to the editor)
	// An audio component that will play the dialogue volume instead of using gameplay statics
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Audio Component" ) )
		UAudioComponent* m_pcAudioComponent;

	// This billboard component will visualise the manager in the map editor.
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Dialgoue Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

	// This dialogue table will hold the dialogue in the level
	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Dialogue Table" ) )
		TMap<FName, FStructDialogueSequence> m_tmDialogueTable;

	// This is a sub class of the desired widget to be used to display dialogue.
	// MAKE SURE TO USE THE BPW_DIALOGUEWIDGETHUD.
	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Dialogue Widget HUD" ) )
		TSubclassOf<UDialogueWidgetHUD> m_tcDialogueWidgetHUD;

#pragma endregion

#pragma region Private Functions
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: PlayDialogueTerm()
	// Author			: Nikodem Hamrol
	// Purpose			: To play the dialogue sequence when initialised.
	//----------------------------------------------------------------------------------------------------------------------------
	void PlayDialogueTerm();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetDialogueTerm()
	// Author			: Nikodem Hamrol
	// Purpose			: To set the dialogue term to be played. To also check if dialogue audio is included and dialogue text.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetDialogueTerm();

#pragma endregion

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: 
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

public:		
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: ADialogueManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	ADialogueManager();

	// The delegate signature to be called when the dialogue finishes with a choice required.
	UPROPERTY( BlueprintAssignable, BlueprintCallable )
		FDialogueUpdatedSignature DialogueUpdate;

		FDialogueFinished DialogueFinished;

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: InitialiseDialogueSequence()
	// Author			: Nikodem Hamrol
	// Purpose			: To initialise the dialogue sequence based on the dialogue ID that was passed through.
	// Parameters		: rnDialogueID - The ID that will find the dialogue sequence within the dialogue table.
	//---------------------------------------------------------------------------------------------------------------------------- 
	UFUNCTION( Category = Dialogue, BlueprintCallable )
		void InitialiseDialogueSequence( const FName& rnDialogueID );

	FStructDialogueSequence& GetDialogueSequence( const FName& rnDialogueID );
};
