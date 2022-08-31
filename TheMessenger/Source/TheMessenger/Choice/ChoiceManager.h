// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_Choice.h"
#include "ChoiceManager.generated.h"

class UBillboardComponent;

class ADialogueManager;
class AInteractable_Base;
class UChoiceSelectionWidget;

UCLASS()
class THEMESSENGER_API AChoiceManager : public AActor
{
	GENERATED_BODY()
	
private:	

	ADialogueManager* m_pcDialogueManager;

	AInteractable_Base* m_pcCharacterInteracted;

	FStructChoiceBranches* m_fsChoiceBranch;

	UChoiceSelectionWidget* m_pcChoiceSelectionWidget;

	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Choice Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Choice Selection Widget" ) )
		TSubclassOf<UChoiceSelectionWidget> m_tcChoiceSelectionWidget;

	UPROPERTY( Category = Dialogue, EditInstanceOnly, meta = ( DisplayName = "Choices" ) )
		TMap<FName, FStructChoiceBranches> m_pfsChoices;

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

	void AddChoices( AInteractable_Base* pcCharacterInteracted );

	void UnHideChoices( FName& rnChoiceID );

};
