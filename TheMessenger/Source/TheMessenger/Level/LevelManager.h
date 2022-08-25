// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum_DayTimeType.h"
#include "LevelManager.generated.h"

class ADirectionalLight;

class ABuilding_Base;
class AChoiceManager;
class ADialogueManager;
class AInteractable_Character;

UCLASS()
class THEMESSENGER_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
private:

	int DayID;

	int m_iActorsFinishedDaySetting;

	TArray<ABuilding_Base*> m_aChangers;

	ADialogueManager* m_pcCurrentDialogueManager;

	UPROPERTY( Category = "Properties", EditInstanceOnly, meta = ( DisplayName = "DayTypes" ) )
		TArray<EDayTimeType> m_aDayTypes;

	UPROPERTY( Category = "Properties|Characters", EditInstanceOnly, meta = ( DisplayName = "Main Characters" ) )
		TArray<AInteractable_Character*> m_apcMainCharacters;

	// An array of all dialogue managers
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue Managers" ) )
		TArray<ADialogueManager*> m_apcDialogueManagers;

	
	UPROPERTY( Category = "Properties|Sky", EditInstanceOnly, meta = ( DisplayName = "Light Night Rotation Y" ) )
		float m_fLightNightRotationY;

	UPROPERTY( Category = "Properties|Sky", EditInstanceOnly, meta = ( DisplayName = "Sky Sphere" ) )
		AActor* m_pcSkySphere;

	UPROPERTY( Category = "Properties|Sky", EditInstanceOnly, meta = ( DisplayName = "Sky Light Source" ) )
		ADirectionalLight* m_pcSkyLightSource;

	// This billboard component will visualise the manager in the map editor.
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Dialgoue Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

	void SetNewDay();

	void SetManagersToCharacters();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ALevelManager();
	
	ADialogueManager& GetCurrentDialogueManager() const;
};
