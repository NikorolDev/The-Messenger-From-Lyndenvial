// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Villager_Base.h"
#include "Villager_Interactable.generated.h"

class ADialogueManager;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API AVillager_Interactable : public AVillager_Base
{
	GENERATED_BODY()

private:
	
	ADialogueManager* m_pcDialogueManager;

	// The dialogue ID that is used to initialise dialogue. The editor set dialogue ID is the intial dialogue ID to play.
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Is Ambient Dialogue" ))
		bool m_bIsAmbientDialogue;

protected:
	virtual void BeginPlay() override;

public:

	virtual void OnInteract_Implementation( AActor* Caller ) override;
};
