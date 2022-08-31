// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enum_VillagerIdleAnimations.h"
#include "InfluentiableThroughChoice.h"
#include "TheMessenger/Interactable/InteractableInterface.h"
#include "Villager_Base.generated.h"

// Forward class Declarations (Engine)
class UAudioComponent;
class UWidgetComponent;

// Forward class Declarations (Game)
class ADialogueManager;
class ATheMessengerCharacter;
class UCharacterOverHead;

UCLASS()
class THEMESSENGER_API AVillager_Base : public ACharacter, public IInteractableInterface, public IInfluentiableThroughChoice
{
	GENERATED_BODY()

private:

	bool m_bIsInSequence;

	bool m_bInteracted;

	ADialogueManager* m_pcDialogueManager;

	// The player character
	ATheMessengerCharacter* m_pcPlayer;

	UCharacterOverHead* m_pcCharacterOverHead;

	UPROPERTY( Category = "Properties|Animations", EditAnywhere, BlueprintReadOnly, meta = ( DisplayName = "Idle Animation", AllowPrivateAccess = true ) )
		EVillagerIdleAnimations m_eIdleAnimation;

	UPROPERTY( Category = "Properties|Character", EditInstanceOnly, meta = ( DisplayName = "Character Name" ) )
		FName m_nCharacterName;

	// The dialogue ID that is used to initialise dialogue. The editor set dialogue ID is the intial dialogue ID to play.
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue ID" ) )
		FName m_nDialogueID;

	UPROPERTY( Category = "Properties|Interaction", EditInstanceOnly, meta = ( DisplayName = "Is Interactable" ) )
		bool m_bIsInteractable;

	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "Player Distance In Sequence" ) )
		float m_fPlayerDistanceInSequence;

	UPROPERTY( Category = Components, EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true, DisplayName = "Audio Component" ) )
		UAudioComponent* m_pcAudioComponent;

	//UPROPERTY( Category = Components, EditDefaultsOnly, BlueprintReadWrite, meta = ( DisplayName = "Widget Component" ) )
	UPROPERTY( Category = Components, EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true, DisplayName = "Widget Component" ) )
		UWidgetComponent* m_pcWidgetComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Initialise();

	UFUNCTION()
		virtual void OnDialogueFinished();

public:
	// Sets default values for this character's properties
	AVillager_Base();

	virtual void OnInteract_Implementation( AActor* Caller ) override;

	virtual void OnFocus_Implementation() override;

	virtual void LostFocus_Implementation() override;

	virtual void OnImpactDialogue_Implementation( const FName& krnDialogueID ) override;

	void PlayAmbientDialogueSequence( FString& krsDialogueText, USoundWave* pcDialogueAudio );

	void SetInteracted( bool bInteracted );

	const bool GetInteracted() const;
	
	void SetIsInSequence( bool bIsInSequence );

	const bool GetIsInteractable() const;

	void SetDialogueID( const FName& krnDialogueID );

	FName& GetDialogueID();

	ADialogueManager& GetDialogueManager() const;

	ATheMessengerCharacter& GetPlayer() const;

	UCharacterOverHead& GetCharatcerOverHead() const;
};
