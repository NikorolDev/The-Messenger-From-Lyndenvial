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

	FVector m_v3InitialLocation;

	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "Off Map Location" ) )
		FVector m_v3OffMapLocation;

	//UPROPERTY( Category = "Properties|Choices", EditAnywhere, meta = ( DisplayName = "Impacted Choices" ) )
	//	TArray<FName> m_anImpactChoiceIDs;

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnImpactActor_Implementation() override;

	//virtual void OnImpactDialogue_Implementation( const FName& krnDialogueID ) override;
};
