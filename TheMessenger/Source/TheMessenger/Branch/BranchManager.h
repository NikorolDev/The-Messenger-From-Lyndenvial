// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheMessenger/Choice/Struct_ChoiceImpact.h"
#include "BranchManager.generated.h"

class UTheMessengerGameInstance;

UCLASS()
class THEMESSENGER_API ABranchManager : public AActor
{
	GENERATED_BODY()
	
private:

	UTheMessengerGameInstance* m_pcGameInstance;

	UPROPERTY( Category = Setup, EditInstanceOnly, meta = ( DisplayName = "Choice Manager Icon" ) )
		TArray<AInteractable_Base*> m_apcCharacters;

	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Choice Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABranchManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetNewDialogueID( FChoiceImpactProperties* krfsChoiceImpactProperties );

};
