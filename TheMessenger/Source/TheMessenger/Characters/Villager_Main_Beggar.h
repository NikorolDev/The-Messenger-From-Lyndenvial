// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Villager_Main.h"
#include "Villager_Main_Beggar.generated.h"

/**
 * 
 */
UCLASS()
class THEMESSENGER_API AVillager_Main_Beggar : public AVillager_Main
{
	GENERATED_BODY()

private:
	UPROPERTY( Category = "Properties|Choices", EditAnywhere, meta = ( DisplayName = "Impacted Choices" ) )
		TArray<FName> m_anImpactChoiceIDs;

public:
	//virtual void OnImpactDialogue_Implementation( const FName& krnDialogueID ) override;
};
