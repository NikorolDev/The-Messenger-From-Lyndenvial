// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Villager_Base.h"
#include "Villager_LordSigismund.generated.h"

class UDayEndScreen;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API AVillager_LordSigismund : public AVillager_Base
{
	GENERATED_BODY()
	
private:

	UDayEndScreen* m_pcDayEndScreen;

	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "End Screen Widget" ) )
		TSubclassOf<UDayEndScreen> m_tcDayEndScreen;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnDialogueFinished() override;

	virtual void OnInteract_Implementation( AActor* Caller ) override;

	virtual void OnImpactDialogue_Implementation( const FName& krnDialogueID ) override;

};
