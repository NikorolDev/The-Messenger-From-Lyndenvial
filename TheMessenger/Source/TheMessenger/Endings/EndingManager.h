// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Struct_CinematicProperties.h"
#include "EndingManager.generated.h"

class UBillboardComponent;

class ALevelManager;
class UCinematic;

UCLASS()
class THEMESSENGER_API AEndingManager : public AActor
{
	GENERATED_BODY()
	
private:
	FCinematicProperties* m_pfsEndingTriggered;

	ALevelManager* m_pcLevelManager;

	UCinematic* m_pcCinematicWidget;

	UPROPERTY( Category = "Properties|Endings Sequence", EditInstanceOnly, meta = ( DisplayName = "Endings" ) )
		TMap<FName, FCinematicProperties> m_tmEndings;

	UPROPERTY( Category = "Properties|Endings Sequence", EditInstanceOnly, meta = ( DisplayName = "Cinematic Widget" ) )
		TSubclassOf<UCinematic> m_tcCinematicWidget;

	// This billboard component will visualise the manager in the map editor.
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Ending Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AEndingManager();

	const bool DisplayEnding();

	UFUNCTION( BlueprintCallable )
		void TriggerEnding( const FName& krnEndingID );
};
