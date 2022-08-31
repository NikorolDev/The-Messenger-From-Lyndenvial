#pragma once

#include "CoreMinimal.h"
#include "TheMessenger/Characters/InfluentiableThroughChoice.h"
#include "Struct_ChoiceImpact.generated.h"

class AVillager_Base;

USTRUCT( BlueprintType )
struct FChoiceImpactProperties
{
	GENERATED_BODY()

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Character Affected" ) )
		TScriptInterface<IInfluentiableThroughChoice> ChoiceInfluenced;


	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Character Affected" ) )
		AVillager_Base* ChoiceInfluencedCharacters = nullptr;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "New Dialogue ID", EditCondition = "CharacterAffected != nullptr" ) )
		FName NewDialogueID;

	// The choice ID of hidden choices
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice ID With Hidden Choices" ) )
		FName ChoiceIDWithHiddenChoices;
};