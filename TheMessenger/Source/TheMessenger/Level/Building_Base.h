// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum_DayTimeType.h"
#include "TheMessenger/Characters/InfluentiableThroughChoice.h"
#include "Building_Base.generated.h"

class UStaticMeshComponent;

UCLASS()
class THEMESSENGER_API ABuilding_Base : public AActor, public IInfluentiableThroughChoice
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABuilding_Base();

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void ChangeOnTimeType(EDayTimeType eDayTimeType);
		void ChangeOnTimeType_Implementation( EDayTimeType eDayTimeType );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void ChangeOnDayNumber( int iDayID );
};
