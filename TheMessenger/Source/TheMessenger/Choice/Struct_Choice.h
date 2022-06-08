#pragma once

#include "Struct_Choice.generated.h"

USTRUCT(BlueprintType)
struct FStructChoiceProperties
{
	GENERATED_BODY()

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Display Text" ) )
		FString ChoiceDisplayText;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Dialogue ID" ) )
		FName DialogueID;
};

USTRUCT( BlueprintType )
struct FStructChoiceBranches
{
	GENERATED_BODY()

		UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Branches" ) )
		TArray<FStructChoiceProperties> ChoiceBranches;
};