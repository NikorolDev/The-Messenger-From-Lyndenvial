// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InfluentiableThroughTimeType.h"
#include "Building_Base.generated.h"

UCLASS()
class THEMESSENGER_API ABuilding_Base : public AActor, public IInfluentiableThroughTimeType
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABuilding_Base();
};
