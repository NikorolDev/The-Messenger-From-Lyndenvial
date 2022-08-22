// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Villager_Base.generated.h"

// Forward class Declarations (Engine)
class UAudioComponent;
class UWidgetComponent;

// Forward class Declarations (Game)
class AAmbientDialogueManager;

UCLASS()
class THEMESSENGER_API AVillager_Base : public ACharacter
{
	GENERATED_BODY()

private:

	AAmbientDialogueManager* m_pcAmbientDialoguemanager;


protected:
	// The dialogue ID that is used to initialise dialogue. The editor set dialogue ID is the intial dialogue ID to play.
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue ID" ) )
		FName m_nDialogueID;

	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Audio Component" ) )
		UAudioComponent* m_pcAudioComponent;

	UPROPERTY( Category = Components, EditDefaultsOnly, BlueprintReadWrite, meta = ( DisplayName = "Widget Component" ) )
		UWidgetComponent* m_pcWidgetComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	AVillager_Base();

	void PlayAmbientDialogueSequence();

};
