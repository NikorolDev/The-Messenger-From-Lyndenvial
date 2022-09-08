#pragma once

#include "CoreMinimal.h"
#include "TheMessenger/Characters/InfluentiableThroughChoice.h"
#include "Struct_ChoiceImpact.generated.h"

// Forward class declaration (Game)
class AVillager_Base;

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FChoiceImpactProperties
// Author				: Nikodem Hamrol
// Purpose				: This struct holds all the impacted actors and the dialogue impact for characters
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FChoiceImpactProperties
{
	GENERATED_BODY()

	// The actor that has the influentiable through choice interface.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Choice Influence Actor Affected" ) )
		TScriptInterface<IInfluentiableThroughChoice> ChoiceInfluencedActor = nullptr;

	// The villager to impact the dialogue on.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Character Affected" ) )
		AVillager_Base* ChoiceInfluencedCharacter = nullptr;

	// The new dialogue ID for the villager.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "New Dialogue ID", EditCondition = "ChoiceInfluencedCharacter != nullptr" ) )
		FName NewDialogueID;
};