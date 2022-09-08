// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Villager_Base.h"
#include "Villager_LordSigismund.generated.h"

class UDayEndScreen;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AVillager_LordSigismund
// Author				: Nikodem Hamrol
// Classes Inherited	: AVillager_Base
// Purpose				: This is the Lord Sigismund class, that is one of the main characters.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API AVillager_LordSigismund : public AVillager_Base
{
	GENERATED_BODY()
	
private:
	// The day end screen needed to open when dialogue sequence is finished.
	UDayEndScreen* m_pcDayEndScreen;

	// The subclass of the day end screen, to get the blueprint version of it.
	UPROPERTY( Category = "Properties|Sequence", EditInstanceOnly, meta = ( DisplayName = "End Screen Widget" ) )
		TSubclassOf<UDayEndScreen> m_tcDayEndScreen;

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay()
	// Author			: Nikodem Hamrol
	// Purpose			: To create the day end screen and to bind a function on dialogue finished
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnDialogueFinished()
	// Author			: Nikodem Hamrol
	// Purpose			: The function called when dialogue finishes, which opens the day end screen.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnDialogueFinished() override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnDialogueFinished()
	// Author			: Nikodem Hamrol
	// Purpose			: When Lord Sigismund is interacted, additionally to the base class interaction will set the player to be
	//					,	in a sequence, locking movement until the next day.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void OnInteract_Implementation( AActor* Caller ) override;
};
