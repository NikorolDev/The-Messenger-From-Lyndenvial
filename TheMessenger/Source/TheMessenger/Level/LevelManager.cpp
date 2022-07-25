// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"

#include <Components/BillboardComponent.h>
#include <Kismet/GameplayStatics.h>

#include "InfluentiableThroughTimeType.h"

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	// Create and setup...
	// Billboard Component (m_pcIconBillboard).
	m_pcIconBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "Diaogue Manager Icon" ) );
	RootComponent = m_pcIconBillboard;
}

void ALevelManager::SetNewDay()
{
	UE_LOG( LogTemp, Display, TEXT( "Building Set" ) );
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Influentiables;
	UGameplayStatics::GetAllActorsWithInterface( GetWorld(), UInfluentiableThroughTimeType::StaticClass(), Influentiables );

	for( AActor* Influentiable : Influentiables )
	{
		m_aChangers.Add( Cast<IInfluentiableThroughTimeType>( Influentiable ) );

		//m_aChangers.Last()->OnFinishedSetting.BindUObject( this, &ALevelManager::SetNewDay );
	}

}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const ETimeType& ALevelManager::GetCurrentTimeType() const
{
	return m_aDayTypes[ DayID ];
}

