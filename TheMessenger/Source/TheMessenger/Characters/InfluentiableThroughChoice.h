// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InfluentiableThroughChoice.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UInfluentiableThroughChoice
// Author				: Nikodem Hamrol
// Classes				: UInterface
// Purpose				: An Interface to allow impact on actors from choice selected.
//-----------------------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UInfluentiableThroughChoice : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THEMESSENGER_API IInfluentiableThroughChoice
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnImpactDialogue( const FName& krnDialogueID )
	// Author			: Nikodem Hamrol
	// Parameter		: krnDialogueID - The new dialogue ID to pass to the character.
	// Purpose			: To change the dialogue based on choice selected.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( Category = "Choice Selected", BlueprintNativeEvent, BlueprintCallable )
		void OnImpactDialogue( const FName& krnDialogueID );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnImpactActor()
	// Author			: Nikodem Hamrol
	// Purpose			: To set a unique impact of the actor on choice selected.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( Category = "Choice Selected", BlueprintNativeEvent, BlueprintCallable )
		void OnImpactActor();
};
