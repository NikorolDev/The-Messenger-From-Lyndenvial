// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UInteractableInterface
// Author				: Nikodem Hamrol
// Classes				: UInterface
// Purpose				: An Interface to allow interaction with interactables.
//-----------------------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THEMESSENGER_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnInteract( AActor* Caller )
	// Author				: Nikodem Hamrol
	// Parameters			: Caller - The actor who called the function
	// Purpose				: Signature of the function which allows an interaction with another actor
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( Category = "Interaction", BlueprintNativeEvent, BlueprintCallable )
		void OnInteract( AActor* Caller );

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: OnFocus()
	// Author				: Nikodem Hamrol
	// Purpose				: Signature of the function which allows the actor to be focused
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( Category = "Interaction", BlueprintNativeEvent, BlueprintCallable )
		void OnFocus();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: LostFocus()
	// Author				: Nikodem Hamrol
	// Purpose				: Signature of the function which allows the actor to be not focused
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( Category = "Interaction", BlueprintNativeEvent, BlueprintCallable )
		void LostFocus();
};
