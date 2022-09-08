// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enum_VillagerIdleAnimations.h"
#include "InfluentiableThroughChoice.h"
#include "TheMessenger/Interactable/InteractableInterface.h"
#include "TheMessenger/Level/Enum_DayTimeType.h"
#include "Villager_Base.generated.h"

// Forward class Declarations (Engine)
class UAudioComponent;
class UWidgetComponent;

// Forward class Declarations (Game)
class ADialogueManager;
class ALevelManager;
class ATheMessengerCharacter;
class UCharacterOverHead;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AVillager_Base
// Author				: Nikodem Hamrol
// Classes Inherited	: ACharacter, IInteractableInterface, InfluentiableThroughChoice
// Purpose				: This base class contains the main common functionality and manager that most children classes will 
//						,	use.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API AVillager_Base : public ACharacter, public IInteractableInterface, public IInfluentiableThroughChoice
{
	GENERATED_BODY()

private:
	// If it has been interacted.
	bool m_bInteracted;

	// If the villager is in a story sequence.
	bool m_bIsInSequence;

	// If the villager is active.
	bool m_bIsActive;

	// The dialogue manager required to bind when finished with a dialogue sequence.
	ADialogueManager* m_pcDialogueManager;

	// The level manager required to check on the day ID for reappearance.
	ALevelManager* m_pcLevelManager;

	// The player character needed to set it for sequence.
	ATheMessengerCharacter* m_pcPlayer;

	// The character over widget needed to display dialogue text and character name as an example.
	UCharacterOverHead* m_pcCharacterOverHead;

	// The animation/pose for the character throughout the game.
	UPROPERTY( Category = "Properties|Animations", EditAnywhere, BlueprintReadOnly, meta = ( DisplayName = "Idle Animation", AllowPrivateAccess = true ) )
		EVillagerIdleAnimations m_eIdleAnimation;

	// The name of the character that will displayed on overhead.
	UPROPERTY( Category = "Properties|Character", EditInstanceOnly, meta = ( DisplayName = "Character Name" ) )
		FName m_nCharacterName;

	// The dialogue ID that is used to initialise dialogue. The editor set dialogue ID is the intial dialogue ID to play.
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue ID" ) )
		FName m_nDialogueID;

	// Whether this character is interactable or not in the game.
	UPROPERTY( Category = "Properties|Interaction", EditInstanceOnly, meta = ( DisplayName = "Is Interactable" ) )
		bool m_bIsInteractable;

	// Whether this character is active at night, which will be hidden at night if false.
	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "Active At Night" ) )
		bool m_bActiveAtNight;

	// Whether this character is completely hidden in the game and won't be seen.
	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "Hidden In Game" ) )
		bool m_bHiddenInGame;

	// The distance that the player will be in front of the villager.
	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "Player Distance In Sequence" ) )
		float m_fPlayerDistanceInSequence;

	// The audio component to play dialogue sound at location.
	UPROPERTY( Category = Components, EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true, DisplayName = "Audio Component" ) )
		UAudioComponent* m_pcAudioComponent;

	// The widget component needed to display the dialogue text and chracter name.
	UPROPERTY( Category = Components, EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true, DisplayName = "Widget Component" ) )
		UWidgetComponent* m_pcWidgetComponent;

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To initialise the character over head widget and get the necessary managers.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: AppearOnThisDay()
	// Author			: Nikodem Hamrol
	// Purpose			: This function is used on story villagers that have to appear on specific days, which will unhide them.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		virtual void AppearOnThisDay() {};

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: AVillager_Base()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	AVillager_Base();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnDialogueFinished()
	// Author			: Nikodem Hamrol
	// Purpose			: To reset the villager from a sequence and interaction. As well as hiding the dialogue text.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		virtual void OnDialogueFinished();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnInteract_Implementation( AActor* Caller )
	// Author			: Nikodem Hamrol
	// Purpose			: To set interaction with the villager that will either play ambient dialogue or set the player in a
	//					,	dialogue seqeunce.
	// Parameters		: Caller - The caller of the interaction.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnInteract_Implementation( AActor* Caller ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnFocus_Implementation()
	// Author			: Nikodem Hamrol
	// Purpose			: This is called when the player is on focus with the villager, which toggle the character overhead on
	//					,	focus overlay.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnFocus_Implementation() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: LostFocus_Implementation()
	// Author			: Nikodem Hamrol
	// Purpose			: This is called when the player loses focus with the villager, which toggle off the character overhead
	//					, completeley.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void LostFocus_Implementation() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnImpactDialogue_Implementation( const FName& krnDialogueID )
	// Author			: Nikodem Hamrol
	// Purpose			: When a villager is impacted by choice through dialogue, it will set their new dialogue ID.
	// Parameters		: krnDialogueID - New dialogue ID to intialise with.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnImpactDialogue_Implementation( const FName& krnDialogueID ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: PlayAmbientDialogueSequence( FString& krsDialogueText, USoundWave* pcDialogueAudio )
	// Author			: Nikodem Hamrol
	// Purpose			: This will play ambient dialogue by playing the sound at location and setting the text.
	// Parameters		: krsDialogueText - The dialogue text to display.
	//					, pcDialogueAudio - Dialogue audio to play.
	//----------------------------------------------------------------------------------------------------------------------------
	void PlayAmbientDialogueSequence( FString& krsDialogueText, USoundWave* pcDialogueAudio );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HideCharacter( bool bHideCharacter )
	// Author			: Nikodem Hamrol
	// Purpose			: This will hide or unhide the character from the game.
	// Parameters		: bHideCharacter - Whether or not should the character be hidden.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( BlueprintCallable )
		void HideCharacter( bool bHideCharacter );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: HideCharacter( EDayTimeType eDayTimeType )
	// Author			: Nikodem Hamrol
	// Purpose			: This will hide or unhide characters based on day time type. This used to hide the villagers that are
	//					,	not ative at night.
	// Parameters		: eDayTimeType - The day time type to determine if the characters are hidden.
	//----------------------------------------------------------------------------------------------------------------------------
	void HideCharacter( EDayTimeType eDayTimeType );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetActive()
	// Author			: Nikodem Hamrol
	// Purpose			: Get the active state of the villager.
	// Returns			: The active state of the villager.
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetActive() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetInteracted( bool bInteracted )
	// Author			: Nikodem Hamrol
	// Purpose			: To set interaction state of the villager
	// Parameters		: bInteracted - Set the vilager to be interacted.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetInteracted( bool bInteracted );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetInteracted()
	// Author			: Nikodem Hamrol
	// Purpose			: Get the interaction state of the character.
	// Returns			: Whether the villager has been interacted already.
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetInteracted() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetActiveAtNight()
	// Author			: Nikodem Hamrol
	// Purpose			: Get the character being active at night.
	// Returns			: Whether the character is active at night.
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetActiveAtNight() const;
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetIsInSequence( bool bIsInSequence )
	// Author			: Nikodem Hamrol
	// Purpose			: To set the sequence state of the villager.
	// Parameters		: bIsInSequence - Set the villager to be in the sequence.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetIsInSequence( bool bIsInSequence );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetIsInteractable()
	// Author			: Nikodem Hamrol
	// Purpose			: Get the character can be interacted.
	// Returns			: Whether the character can be interacted in the game.
	//----------------------------------------------------------------------------------------------------------------------------
	const bool GetIsInteractable() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetDialogueID( const FName& krnDialogueID )
	// Author			: Nikodem Hamrol
	// Purpose			: To set a new dialogue ID for the villager to initialise rom dialogue manager.
	// Parameters		: krnDialogueID - The desired dialogue ID for the dilaogue manager.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( BlueprintCallable )
		void SetDialogueID( const FName& krnDialogueID );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetDialogueID()
	// Author			: Nikodem Hamrol
	// Purpose			: Get the dialogue ID that is set for the villager.
	// Returns			: The dialogue ID that villager has been set.
	//----------------------------------------------------------------------------------------------------------------------------
	FName& GetDialogueID();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetDialogueManager()
	// Author			: Nikodem Hamrol
	// Purpose			: The dialogue manager for the setting the bind for children classes
	// Returns			: The dialogue manager in the level.
	//----------------------------------------------------------------------------------------------------------------------------
	ADialogueManager& GetDialogueManager() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetLevelManager()
	// Author			: Nikodem Hamrol
	// Purpose			: The level manager needed to track days for setting appearance.
	// Returns			: The level manager in the level.
	//----------------------------------------------------------------------------------------------------------------------------
	ALevelManager& GetLevelManager() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetPlayer()
	// Author			: Nikodem Hamrol
	// Purpose			: The player needed to the player in sequence for Lord Sigismund
	// Returns			: The player character.
	//----------------------------------------------------------------------------------------------------------------------------
	ATheMessengerCharacter& GetPlayer() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetCharatcerOverHead()
	// Author			: Nikodem Hamrol
	// Purpose			: The character over head widget needed to hide the dialogue within the dialogue manager.
	// Returns			: The character over head widget.
	//----------------------------------------------------------------------------------------------------------------------------
	UCharacterOverHead& GetCharatcerOverHead() const;
};
