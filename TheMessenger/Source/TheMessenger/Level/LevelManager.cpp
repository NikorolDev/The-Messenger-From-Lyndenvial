// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"

#include <Components/BillboardComponent.h>
#include <Engine/DirectionalLight.h>
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include <Misc/OutputDeviceNull.h>

#include "Building_Base.h"
#include "TheMessenger/TheMessengerCharacter.h"

// Sets default values
ALevelManager::ALevelManager()
	: m_iDayID(0)
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
	m_iDayID++;

	ChangeTime();

	OnChangedDay.Broadcast();

	m_pcPlayer->SetLocationToSpawn();
	
	//FRotator CurrentLightRotation = m_pcSkyLightSource->GetActorRotation();
	//
	//switch( m_aDayTypes[ m_iDayID ] )
	//{
	//	case EDayTimeType::Day:
	//	{
	//		m_pcSkyLightSource->SetActorRotation( FRotator( m_fLightDayRotationY, CurrentLightRotation.Yaw, CurrentLightRotation.Roll ) );
	//	}
	//	case EDayTimeType::Night:
	//	{
	//		m_pcSkyLightSource->SetActorRotation( FRotator( m_fLightNightRotationY, CurrentLightRotation.Yaw, CurrentLightRotation.Roll ) );
	//	}
	//}
	//
	//
	//
	//
	////for( int i = 0; i < m_aChangers.Num(); ++i )
	////{
	////	m_aChangers[ i ]->ChangeOnTimeType(m_aDayTypes[m_iDayID]);
	////}
	//
	//
	//
	//
	//if( m_pcSkySphere )
	//{
	//	FOutputDeviceNull outputDevice;
	//	m_pcSkySphere->CallFunctionByNameWithArguments( TEXT( "UpdateSunDirection" ), outputDevice, nullptr, true );
	//}


}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();

	m_pcPlayer = Cast<ATheMessengerCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 ) );

	TActorIterator<ABuilding_Base> BuildingsIterator = TActorIterator<ABuilding_Base>( GetWorld(), ABuilding_Base::StaticClass() );
	
	while( BuildingsIterator )
	{
		m_aChangers.Add( *BuildingsIterator );
	
		BuildingsIterator.operator++();
	}


	// Make a temporary array of actors that will get all actors with the influentiable interface.
	//TArray<AActor*> Influentiables;
	//UGameplayStatics::GetAllActorsWithInterface( GetWorld(), UInfluentiableThroughTimeType::StaticClass(), Influentiables );

	// Loop through all influetiable actors
	//for( AActor* Influentiable : Influentiables )
	//{
	//	// Cast it as influentiable and add it to a different array that will be used to check if actors have set their new day properties.
	//	m_aChangers.Add( Cast<IInfluentiableThroughTimeType>( Influentiable ) );
	//	
	//	// Bind the recently added influentiable.
	//	m_aChangers.Last()->OnFinishedSetting.BindUObject( this, &ALevelManager::SetNewDay );
	//}

	// Set necessary managers to characters.
	//SetManagersToCharacters();

	//SetNewDay();

	ChangeTime();
}

void ALevelManager::ChangeTime()
{
	for( int i = 0; i < m_aChangers.Num(); ++i )
	{
		m_aChangers[ i ]->ChangeOnTimeType( m_aDayTypes[ m_iDayID ] );
	}

	FRotator CurrentLightRotation = m_pcSkyLightSource->GetActorRotation();

	switch( m_aDayTypes[ m_iDayID ] )
	{
		case EDayTimeType::Day:
		{
			m_pcSkyLightSource->SetActorRotation( FRotator( m_fLightDayRotationY, CurrentLightRotation.Yaw, CurrentLightRotation.Roll ) );
			break;
		}
		case EDayTimeType::Night:
		{
			m_pcSkyLightSource->SetActorRotation( FRotator( m_fLightNightRotationY, CurrentLightRotation.Yaw, CurrentLightRotation.Roll ) );
			break;
		}
	}

	if( m_pcSkySphere )
	{
		FOutputDeviceNull outputDevice;
		m_pcSkySphere->CallFunctionByNameWithArguments( TEXT( "UpdateSunDirection" ), outputDevice, nullptr, true );
	}
}

int ALevelManager::GetDayID() const									{ return m_iDayID; }
