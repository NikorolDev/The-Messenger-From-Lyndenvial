// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "TheMessenger/Choice/Struct_Choice.h"
#include "Interactable_Base.generated.h"

class ADialogueManager;

UCLASS()
class THEMESSENGER_API AInteractable_Base : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
private:
	ADialogueManager* m_pcDialogueManager;

	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Dialogue ID" ) )
		FName m_nDialogueID;

	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Choices" ) )
		TMap<FName, FStructChoiceBranches> m_pfsChoices;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:		
	// Sets default values for this actor's properties
	AInteractable_Base();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnInteract( AActor* Caller )
	// Author				: Nikodem Hamrol
	// Parameters			: Caller - The actor who called the function
	// Purpose				: Signature of the function which allows an interaction with another actor
	//-----------------------------------------------------------------------------------------------------------------------------
	//UFUNCTION( Category = "Interaction", BlueprintNativeEvent, BlueprintCallable )
	//	void OnInteract( AActor* Caller );
	virtual void OnInteract_Implementation( AActor* Caller ) override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnFocus()
	// Author				: Nikodem Hamrol
	// Purpose				: Signature of the function which allows the actor to be focused
	//-----------------------------------------------------------------------------------------------------------------------------
	//UFUNCTION( Category = "Interaction", BlueprintNativeEvent, BlueprintCallable )
	//	void OnFocus();
	virtual void OnFocus_Implementation() override;

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: LostFocus()
	// Author				: Nikodem Hamrol
	// Purpose				: Signature of the function which allows an interaction with another actor
	//-----------------------------------------------------------------------------------------------------------------------------
	//UFUNCTION( Category = "Interaction", BlueprintNativeEvent, BlueprintCallable )
	//	void LostFocus();
	virtual void LostFocus_Implementation() override;
};
