// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractableInterface.h"
#include "Interactable_Character.generated.h"

class UAudioComponent;
class UWidgetComponent;

class ADialogueManager;
class UDialogueWidgetHUD;

UCLASS()
class THEMESSENGER_API AInteractable_Character : public ACharacter, public IInteractableInterface
{
	GENERATED_BODY()

private:
	// Whether the player has already interacted with the character.
	bool m_bInteracted;

	// The dialogue manager needed to play the dialogue once the player interacts with the character.
	ADialogueManager* m_pcDialogueManager;

	UDialogueWidgetHUD* m_pcDialogueWidget;

	// An audio component that will play the dialogue volume instead of using gameplay statics
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Audio Component" ) )
		UAudioComponent* m_pcAudioComponent;

	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Widget Component" ) )
		UWidgetComponent* m_pcWidgetComponent;

	// The dialogue ID that is used to initialise dialogue. The editor set dialogue ID is the intial dialogue ID to play.
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue ID" ))
		FName m_nDialogueID;

	// Should the character follow the player after interaction.
	UPROPERTY( Category = "Properties|Movement", EditInstanceOnly, meta = ( DisplayName = "Will Follow Player" ) )
		bool m_bWillFollowPlayer;

protected:
	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void FollowPlayer();

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
