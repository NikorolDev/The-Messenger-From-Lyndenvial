// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TheMessenger/Interactable/InteractableInterface.h"
#include "Villager_Base.generated.h"

// Forward class Declarations (Engine)
class UAudioComponent;
class UWidgetComponent;

// Forward class Declarations (Game)
class AAmbientDialogueManager;
class UCharacterOverHead;

UCLASS()
class THEMESSENGER_API AVillager_Base : public ACharacter, public IInteractableInterface
{
	GENERATED_BODY()

private:

	AAmbientDialogueManager* m_pcAmbientDialogueManager;

	UCharacterOverHead* m_pcCharacterOverHead;

	UPROPERTY( Category = "Properties|Character", EditInstanceOnly, meta = ( DisplayName = "Character Name" ) )
		FName m_nCharacterName;

	// The dialogue ID that is used to initialise dialogue. The editor set dialogue ID is the intial dialogue ID to play.
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue ID" ) )
		FName m_nDialogueID;

	UPROPERTY( Category = "Properties|Interaction", EditInstanceOnly, meta = ( DisplayName = "Is Interactable" ) )
		bool m_bIsInteractable;

	UPROPERTY( Category = Components, EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true, DisplayName = "Audio Component" ) )
		UAudioComponent* m_pcAudioComponent;

	//UPROPERTY( Category = Components, EditDefaultsOnly, BlueprintReadWrite, meta = ( DisplayName = "Widget Component" ) )
	UPROPERTY( Category = Components, EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true, DisplayName = "Widget Component" ) )
		UWidgetComponent* m_pcWidgetComponent;


protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Initialise();

public:
	// Sets default values for this character's properties
	AVillager_Base();

	virtual void OnFocus_Implementation() override;

	virtual void LostFocus_Implementation() override;

	void PlayAmbientDialogueSequence( FString& krsDialogueText, USoundWave* pcDialogueAudio );

	const bool GetIsInteractable() const;

	FName& GetDialogueID();

	AAmbientDialogueManager& GetAmbientDialogueManager() const;

	UCharacterOverHead& GetCharatcerOverHead() const;
};
