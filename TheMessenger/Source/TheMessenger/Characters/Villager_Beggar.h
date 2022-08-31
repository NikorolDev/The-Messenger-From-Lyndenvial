// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Villager_Base.h"
#include "Villager_Beggar.generated.h"

/**
 * 
 */
UCLASS()
class THEMESSENGER_API AVillager_Beggar : public AVillager_Base
{
	GENERATED_BODY()

private:
	UPROPERTY( Category = "Properties|Choices", EditAnywhere, meta = ( DisplayName = "Impacted Choices" ) )
		TArray<FName> m_anImpactChoiceIDs;

public:
	//virtual void OnImpactDialogue_Implementation( const FName& krnDialogueID ) override;
};
