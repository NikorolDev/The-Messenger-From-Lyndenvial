// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enum_DayTimeType.h"
#include "Building_Base.generated.h"

class UStaticMeshComponent;

UCLASS()
class THEMESSENGER_API ABuilding_Base : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY( Category = "Properties|Windows", EditDefaultsOnly, BlueprintReadOnly )
		FVector m_v3DefaultWindowColour;

	UPROPERTY( Category = "Properties|Windows", EditDefaultsOnly, BlueprintReadOnly )
		FVector m_v3NightWindowColour;

	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
		TArray<UStaticMeshComponent*> m_aWindows;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABuilding_Base();

	//UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void SetForNextDay(EDayTimeType eDayTimeType);
};
