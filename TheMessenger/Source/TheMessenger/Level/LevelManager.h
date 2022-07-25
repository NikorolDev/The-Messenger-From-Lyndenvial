// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

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

	UPROPERTY( Category = "Properties", EditInstanceOnly, meta = ( DisplayName = "DayTypes" ) )
		TArray<ETimeType> m_aDayTypes;

	// This billboard component will visualise the manager in the map editor.
	UPROPERTY( Category = Components, EditDefaultsOnly, meta = ( DisplayName = "Dialgoue Manager Icon" ) )
		UBillboardComponent* m_pcIconBillboard;

	void SetNewDay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ALevelManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION( BlueprintPure )
		const ETimeType& GetCurrentTimeType() const;
};
