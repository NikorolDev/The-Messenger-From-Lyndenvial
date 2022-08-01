// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_HintProperties.h"
#include "HintsManager.generated.h"

// Forward class declarations (Engine)
class UBillboardComponent;

// Forward class declarations (Game)
class UPlayerHUD;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AHintsManager
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor
// Purpose				: This class will hold all the objectives, display the current one using the player HUD.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API AHintsManager : public AActor
{
	GENERATED_BODY()
	
private:
	FHintProperties* m_pfsCurrentHint;

	UPlayerHUD* m_pcPlayerHUD;

	// This billboard will visualise the manager in the map editor.
	UPROPERTY( EditDefaultsOnly, meta = ( DisplayName = "Tooltip Manager Display" ) )
		UBillboardComponent* m_pcHintsManagerBillboard;

	UPROPERTY( EditInstanceOnly, meta = ( DisplayName = "Hints" ) )
		TMap<FName, FHintProperties> m_tmHints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AHintsManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetObjective( FName& rcnObjectiveID );

};
