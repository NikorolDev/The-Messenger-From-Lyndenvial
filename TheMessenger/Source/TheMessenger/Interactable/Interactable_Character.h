// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractableInterface.h"
#include "Interactable_Character.generated.h"

class ADialogueManager;

UCLASS()
class THEMESSENGER_API AInteractable_Character : public ACharacter, public IInteractableInterface
{
	GENERATED_BODY()

private:
	// The dialogue manager needed to play the dialogue once the player interacts with the character.
	ADialogueManager* m_pcDialogueManager;

	// The dialogue ID that is used to initialise dialogue. The editor set dialogue ID is the intial dialogue ID to play.
	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Dialogue ID" ) )
		FName m_nDialogueID;

protected:
	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

public:	
	// Sets default values for this character's properties
	AInteractable_Character();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract_Implementation( AActor* Caller ) override;

	virtual void OnFocus_Implementation() override;

	virtual void LostFocus_Implementation() override;

	void SetDialogueID( const FName& krnDialogueID );

};
