// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum_DayTimeType.h"
#include "LevelManager.generated.h"

// Forward class Declarations (Engine)
class ADirectionalLight;
class UBillboardComponent;

// Forward class Declarations (Game)
class ABuilding_Base;
class AChoiceManager;
class ADialogueManager;
class ATheMessengerCharacter;
class AVillager_Base;

// Delegates
DECLARE_MULTICAST_DELEGATE( FChangeDay );

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ADialogueManager
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor
// Purpose				: This class controls the necessary actors in the level like switching states based on time type and
//						,	day count.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
private:
	// The day ID to signify the current day.
	int m_iDayID;

	// The current day time type set using the day ID.
	EDayTimeType m_eCurrentDayTimeType;

	// An array of building to switch states based on time type.
	TArray<ABuilding_Base*> m_aBuildings;

	// An array of villagers to hide the villagers at night time.
	TArray<AVillager_Base*> m_aVillagers;

	// Gets the player to set it back to spawn point on next day.
	ATheMessengerCharacter* m_pcPlayer;

	// An array of time types to switched when setting to a new day.
	UPROPERTY( Category = "Properties", EditInstanceOnly, meta = ( DisplayName = "DayTypes" ) )
		TArray<EDayTimeType> m_aDayTypes;

	// The rotation of the light source on Y at day time.
	UPROPERTY( Category = "Properties|Sky", EditInstanceOnly, meta = ( DisplayName = "Light Day Rotation Y" ) )
		float m_fLightDayRotationY;
	
	// The rotation of the light source on Y at night time.
	UPROPERTY( Category = "Properties|Sky", EditInstanceOnly, meta = ( DisplayName = "Light Night Rotation Y" ) )
		float m_fLightNightRotationY;

	// The sky sphere needed to update when setting the rotation of the light source.
	UPROPERTY( Category = "Properties|Sky", EditInstanceOnly, meta = ( DisplayName = "Sky Sphere" ) )
		AActor* m_pcSkySphere;

	// The light source used to rotate it to set night and day time.
	UPROPERTY( Category = "Properties|Sky", EditInstanceOnly, meta = ( DisplayName = "Sky Light Source" ) )
		ADirectionalLight* m_pcSkyLightSource;

	// This billboard component will visualise the manager in the map editor.
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Dialgoue Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: To get all of the actors needed to change through time type and day ID.
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

public:	
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: ALevelManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	ALevelManager();

	// The delegate signature to be called when the day changes.
	FChangeDay OnChangedDay;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetNewDay()
	// Author			: Nikodem Hamrol
	// Purpose			: Sets new day when continuing from the day end screen.
	//---------------------------------------------------------------------------------------------------------------------------- 
	void SetNewDay();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: ChangeTime()
	// Author			: Nikodem Hamrol
	// Purpose			: Change to a new time when the next day is set.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( BlueprintCallable )
		void ChangeTime();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetDayID()
	// Author			: Nikodem Hamrol
	// Purpose			: To get the day ID for matching on some actors that need methods done on a specific day.
	// Returns			: The current Day ID.
	//----------------------------------------------------------------------------------------------------------------------------
	int GetDayID() const;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetCurrentDayTimeType( EDayTimeType eDayTimeType );
	// Author			: Nikodem Hamrol
	// Purpose			: To set the day time type to be able to change the time.
	// Parameters		: eDayTimeType - The desired day time type.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( BlueprintCallable )
		void SetCurrentDayTimeType( EDayTimeType eDayTimeType );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetCurrentDayTimeType();
	// Author			: Nikodem Hamrol
	// Purpose			: To get the current day time type.
	// Parameters		: The current day time type.
	//----------------------------------------------------------------------------------------------------------------------------
	EDayTimeType GetCurrentDayTimeType() const;
};
