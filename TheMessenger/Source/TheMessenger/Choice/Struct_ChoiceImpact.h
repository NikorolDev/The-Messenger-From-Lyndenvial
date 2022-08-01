#pragma once

#include "CoreMinimal.h"
#include "Struct_ChoiceImpact.generated.h"

class AInteractable_Character;

USTRUCT( BlueprintType )
struct FChoiceImpactProperties
{
	GENERATED_BODY()


	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Character Affected Tag" ) )
		AInteractable_Character* CharacterAffectedTag;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "New Dialogue ID", EditCondition = "CharacterAffected != nullptr" ) )
		FName NewDialogueID;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Hint ID" ) )
		FName HintID;
};