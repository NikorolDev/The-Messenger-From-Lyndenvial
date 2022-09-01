#pragma once

#include "CoreMinimal.h"
#include "TheMessenger/Characters/InfluentiableThroughChoice.h"
#include "Struct_ChoiceImpact.generated.h"

class AVillager_Base;

USTRUCT( BlueprintType )
struct FChoiceImpactProperties
{
	GENERATED_BODY()

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Influence Actor Affected" ) )
		TScriptInterface<IInfluentiableThroughChoice> ChoiceInfluencedActor = nullptr;


	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Character Affected" ) )
		AVillager_Base* ChoiceInfluencedCharacter = nullptr;

	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "New Dialogue ID", EditCondition = "ChoiceInfluencedCharacter != nullptr" ) )
		FName NewDialogueID;

	// The choice ID of hidden choices
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice ID With Hidden Choices" ) )
		FName ChoiceIDWithHiddenChoices;
};