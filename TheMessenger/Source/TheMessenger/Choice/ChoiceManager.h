// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_Choice.h"
#include "ChoiceManager.generated.h"

class ADialogueManager;

UCLASS()
class THEMESSENGER_API AChoiceManager : public AActor
{
	GENERATED_BODY()
	
private:	
	FStructChoiceBranches* m_fsChoiceBranch;

	ADialogueManager* m_pcDialogueManager;

	UFUNCTION()
		void DisplayChoices( FName ChoiceID );

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:		
	// Sets default values for this actor's properties
	AChoiceManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddChoices( FStructChoiceBranches* tmChoices );

	void UnloadChoices();

};
