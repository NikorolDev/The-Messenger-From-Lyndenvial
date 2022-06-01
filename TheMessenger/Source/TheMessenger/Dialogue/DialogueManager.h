// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogueManager.generated.h"

class UBillboardComponent;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: ADialogueManager
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor
// Purpose				: This class will hold all the dialogue and display the correct sequence onto the widget within a 
//						,	level.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API ADialogueManager : public AActor
{
	GENERATED_BODY()
	
private:
#pragma region Private Variables (not exposed to the editor)
	bool m_bIsDialogueSequenceInitialised;


#pragma endregion

#pragma region Private Variables (exposed to the editor)
	// This billboard component will visualise the manager in the map editor.
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Dialgoue Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

#pragma endregion

protected:
	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: BeginPlay() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: 
	//----------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;

public:		
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: ADialogueManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	ADialogueManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
