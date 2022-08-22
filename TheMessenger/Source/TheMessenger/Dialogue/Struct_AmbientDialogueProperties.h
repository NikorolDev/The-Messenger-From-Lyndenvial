#pragma once

#include "Struct_DialogueProperties.h"
#include "Struct_AmbientDialogueProperties.generated.h"

// Forward class declaration
class AVillager_Base;

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FStructAmbientDialogueProperties
// Author				: Nikodem Hamrol
// Purpose				: This struct is made to store the properties of each dialogue, such as text and duration of display 
//						,	and audio files.
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FAmbientDialogueProperties : public FStructDialogueProperties
{
	GENERATED_BODY()

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		AVillager_Base* CharacterToSpeak = nullptr;
};

USTRUCT(BlueprintType)
struct FAmbientDialogueSequence
{
	GENERATED_BODY()

	UPROPERTY( EditinstanceOnly, BlueprintReadOnly )
		TArray<struct FAmbientDialogueProperties> AmbientDialogueSequence;
};