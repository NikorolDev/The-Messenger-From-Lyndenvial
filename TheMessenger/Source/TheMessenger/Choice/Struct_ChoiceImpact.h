#pragma once

#include "CoreMinimal.h"
#include "Struct_ChoiceImpact.generated.h"

class AInteractable_Character;

USTRUCT( BlueprintType )
struct FChoiceImpactProperties
{
	GENERATED_BODY()


	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Character Affected" ) )
		AInteractable_Character* CharacterAffected;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "New Dialogue ID", EditCondition = "CharacterAffected != nullptr" ) )
		FName NewDialogueID;

	// The choice ID of hidden choices
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice ID With Hidden Choices" ) )
		FName ChoiceIDWithHiddenChoices;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Hint ID" ) )
		FName HintID;
};