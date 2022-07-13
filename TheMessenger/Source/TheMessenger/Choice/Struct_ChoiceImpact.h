#pragma once

#include "CoreMinimal.h"
#include "Struct_ChoiceImpact.generated.h"

class AInteractable_Base;

USTRUCT( BlueprintType )
struct FChoiceImpactProperties
{
	GENERATED_BODY()


	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Character Affected Tag" ) )
		AInteractable_Base* CharacterAffectedTag;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "New Dialogue ID", EditCondition = "CharacterAffected != nullptr" ) )
		FName NewDialogueID;
};