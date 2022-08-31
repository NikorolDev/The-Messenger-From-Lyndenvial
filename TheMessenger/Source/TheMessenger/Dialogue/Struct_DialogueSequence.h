#pragma once

#include "Struct_DialogueProperties.h"
#include "Struct_DialogueSequence.generated.h"

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FStructDialogueSequence
// Author				: Nikodem Hamrol
// Purpose				: This struct is made to store the array of the dialogue properties to be used in the TMap in the 
//						,	dialogue manager.
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FStructDialogueSequence
{
	GENERATED_BODY()

	// Whether the dialogue needs a choice to contine with the dialogue or completely finishes.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Is Choice Required" ) )
		bool bIsChoiceRequired;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Is A Sequence" ) )
		bool bIsASequence;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( EditCondition = "bIsChoiceRequired" ) )
		FName ChoiceID;

	// The dialogue sequence that will displayed on the screen.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		TArray<struct FStructDialogueProperties> DialogueSequence;
};
