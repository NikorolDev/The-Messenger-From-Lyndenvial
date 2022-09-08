#pragma once

#include "CoreMinimal.h"
#include "Struct_ChoiceImpact.h"
#include "Struct_Choice.generated.h"

// Enum of type buttons for colouring and hiding.
UENUM(BlueprintType)
enum class EChoiceType : uint8
{
	Hidden,
	Main,
	Optional,
	Exit
};

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FStructChoiceProperties
// Author				: Nikodem Hamrol
// Purpose				: This struct is made to store the properties of each choice, which how are they displayed and what 
//						,	does it impact.
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStructChoiceProperties
{
	GENERATED_BODY()
	
	// The choice type the way of colouring the button.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Type" ) )
		EChoiceType eChoiceType;

	// The button display choice.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Display Text" ) )
		FString ChoiceDisplayText;

	// The dialogue ID to continue from the choice.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Dialogue ID" ) )
		FName DialogueID;

	// The Hint ID to pop up after dialogue finishes.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Hint ID" ) )
		FName HintID;

	// Should the choice trigger an ending.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Trigger Ending" ) )
		bool TriggerEnding;

	// The ending ID that will be triggered.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Ending ID", EditCondition = "TriggerEnding" ) )
		FName EndingID;

	// Impact properties array.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Impact Properties" ) )
		TArray<FChoiceImpactProperties> ChoiceImpactProperties;
};

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FStructChoiceBranches
// Author				: Nikodem Hamrol
// Purpose				: This struct is made to make an array of choice properties to be used in a map
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FStructChoiceBranches
{
	GENERATED_BODY()

	// Array of choice porperties.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Branches" ) )
		TArray<FStructChoiceProperties> ChoiceBranches;
};