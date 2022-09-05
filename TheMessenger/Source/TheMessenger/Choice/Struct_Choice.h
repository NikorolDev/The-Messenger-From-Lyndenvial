#pragma once

#include "CoreMinimal.h"
#include "Struct_ChoiceImpact.h"
#include "Struct_Choice.generated.h"

class AInteractable_Base;

UENUM(BlueprintType)
enum class EChoiceType : uint8
{
	Hidden,
	Main,
	Optional,
	Exit
};

USTRUCT(BlueprintType)
struct FStructChoiceProperties
{
	GENERATED_BODY()

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Type" ) )
		EChoiceType eChoiceType;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Display Text" ) )
		FString ChoiceDisplayText;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Dialogue ID" ) )
		FName DialogueID;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Hint ID" ) )
		FName HintID;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Trigger Ending" ) )
		bool TriggerEnding;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Ending ID", EditCondition = "TriggerEnding" ) )
		FName EndingID;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Impact Properties" ) )
		TArray<FChoiceImpactProperties> ChoiceImpactProperties;
};

USTRUCT( BlueprintType )
struct FStructChoiceBranches
{
	GENERATED_BODY()

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Branches" ) )
		TArray<FStructChoiceProperties> ChoiceBranches;
};