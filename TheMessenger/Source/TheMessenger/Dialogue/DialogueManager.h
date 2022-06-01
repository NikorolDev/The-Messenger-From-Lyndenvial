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
class UDialogueWidgetHUD;

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


	float m_fDialogueTermTime;


	int m_iDialogueID;

	int m_iNumberOfDialogueTerms;
	
	// An instance of the dialogue 
	FStructDialogueSequence* m_pfsDialogueSequence;

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
		TMap<FString, FStructDialogueSequence> m_tmDialogueTable;

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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION( Category = Dialogue, BlueprintCallable )
		void InitialiseDialogueSequence( const FString& rsDialogueID );
};
