// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum_DayTimeType.h"
#include "TheMessenger/Characters/InfluentiableThroughChoice.h"
#include "Building_Base.generated.h"

// Forward class Declarations (Engine)
class UStaticMeshComponent;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ADialogueManager
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor, IInfluentiableThroughChoice
// Purpose				: This class holds just the functionality to change on time type or on day number for Blueprint actors.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API ABuilding_Base : public AActor, public IInfluentiableThroughChoice
{
	GENERATED_BODY()

public:	
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: ADialogueManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	ABuilding_Base();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ChangeOnTimeType( EDayTimeType eDayTimeType )
	// Author			: Nikodem Hamrol
	// Purpose			: To change on time type, mainly used on lampposts.
	// Parameters		: eDayTimeType - The time type used to change appearance, like turning lights on.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void ChangeOnTimeType( EDayTimeType eDayTimeType );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ChangeOnDayNumber( int iDayID )
	// Author			: Nikodem Hamrol
	// Purpose			: To change on day ID.
	// Parameters		: iDayID - The desired day to change on.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void ChangeOnDayNumber( int iDayID );
};
