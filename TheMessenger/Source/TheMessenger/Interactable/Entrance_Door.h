// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Entrance_Door.generated.h"

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: AEntrance_Door
// Author				: Nikodem Hamrol
// Classes Inherited	: AActor and IInteractableInterface
// Purpose				: This class will be responsible for taking the player to a location in the world when interacted.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API AEntrance_Door : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
private:	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AEntrance_Door();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
