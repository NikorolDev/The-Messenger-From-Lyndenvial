// Fill out your copyright notice in the Description page of Project Settings.


#include "Building_Base.h"

// Sets default values
ABuilding_Base::ABuilding_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ABuilding_Base::ChangeOnTimeType_Implementation( EDayTimeType eDayTimeType )
{
}

// Called when the game starts or when spawned
void ABuilding_Base::BeginPlay()
{
	Super::BeginPlay();

	
}
