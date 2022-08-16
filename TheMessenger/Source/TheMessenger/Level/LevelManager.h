// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"


class AChoiceManager;
class ADialogueManager;
class AInteractable_Character;
class IInfluentiableThroughTimeType;

UENUM( BlueprintType )
enum class ETimeType : uint8
{
	Day,
	Night
};


UCLASS()
class THEMESSENGER_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
private:

	int DayID;

	TArray<IInfluentiableThroughTimeType*> m_aChangers;

	ADialogueManager* m_pcCurrentDialogueManager;

	UPROPERTY( Category = "Properties", EditInstanceOnly, meta = ( DisplayName = "DayTypes" ) )
		TArray<ETimeType> m_aDayTypes;

	// An array of all choice managers
	UPROPERTY( Category = "Properties|Choice", EditInstanceOnly, meta = ( DisplayName = "Choice Managers" ) )
		TArray<AChoiceManager*> m_apcChoiceManagers;

	UPROPERTY( Category = "Properties|Characters", EditInstanceOnly, meta = ( DisplayName = "Main Characters" ) )
		TArray<AInteractable_Character*> m_apcMainCharacters;

	// An array of all dialogue managers
	UPROPERTY( Category = "Properties|Dialogue", EditInstanceOnly, meta = ( DisplayName = "Dialogue Managers" ) )
		TArray<ADialogueManager*> m_apcDialogueManagers;

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

	UFUNCTION( BlueprintPure )
		const ETimeType& GetCurrentTimeType() const;
	
	ADialogueManager& GetCurrentDialogueManager() const;
};
