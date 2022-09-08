// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"

#include <Components/BillboardComponent.h>
#include <Engine/DirectionalLight.h>
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include <Misc/OutputDeviceNull.h>

#include "Building_Base.h"
#include "TheMessenger/Characters/Villager_Base.h"
#include "TheMessenger/TheMessengerCharacter.h"

// Sets default values
ALevelManager::ALevelManager()
	: m_iDayID				(0)
	, m_eCurrentDayTimeType (EDayTimeType::Day)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Billboard Component (m_pcIconBillboard).
	m_pcIconBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "Diaogue Manager Icon" ) );
	RootComponent = m_pcIconBillboard;
}

void ALevelManager::BeginPlay()
{
	// Call the Actor's begin play.
	Super::BeginPlay();

	// Get the player character that is in the world.
	m_pcPlayer = Cast<ATheMessengerCharacter>( UGameplayStatics::GetPlayerCharacter( GetWorld(), 0 ) );

	// Make actor iterators for the buildings and the characters.
	TActorIterator<ABuilding_Base> BuildingsIterator = TActorIterator<ABuilding_Base>( GetWorld(), ABuilding_Base::StaticClass() );
	TActorIterator<AVillager_Base> CharactersIterator = TActorIterator<AVillager_Base>( GetWorld(), AVillager_Base::StaticClass() );
	
	// The buildings are needed to set their day and night states, for example for lampposts.
	// While there is a building remaing in the iterator.
	while( BuildingsIterator )
	{
		// Add the building to the array
		m_aBuildings.Add( *BuildingsIterator );
	
		// Move on to the next building.
		BuildingsIterator.operator++();
	}

	// Villagers are needed to set some to be hidden away at nght time to show that there is less people at night.
	// While there is a villager remaining in the iterator.
	while( CharactersIterator )
	{
		// Make a temporary villager from the current villager in the iterator.
		AVillager_Base* pcvillager = *CharactersIterator;

		// Check if the villager is not active at night.
		if( !pcvillager->GetActiveAtNight() )
		{
			// Add that villager to the array.
			m_aVillagers.Add( pcvillager );
		}

		// Move on to the next Villager.
		CharactersIterator.operator++();
	}

	// Change Time, which will be day time.
	ChangeTime();
}

void ALevelManager::ChangeTime()
{
	// Broadcast event when the day has changed.
	OnChangedDay.Broadcast();

	// Loop through all the buildings to change on time type.
	for( int i = 0; i < m_aBuildings.Num(); ++i )
	{
		m_aBuildings[ i ]->ChangeOnTimeType( m_eCurrentDayTimeType );
	}

	// Loop through all the villagers to hide them from level, based on the current day time type.
	for( int iVillagerID = 0; iVillagerID < m_aVillagers.Num(); ++iVillagerID )
	{
		m_aVillagers[ iVillagerID ]->HideCharacter( m_eCurrentDayTimeType );
	}

	// Get light source's rotation to keep the yaw and roll the same as it needs to affect the pitch.
	FRotator CurrentLightRotation = m_pcSkyLightSource->GetActorRotation();

	// Based on the day time type, set the light source's rotation.
	switch( m_eCurrentDayTimeType )
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

	// Check if the sky sphere is set.
	if( m_pcSkySphere )
	{
		// Update the sun's direction. So it updates the sky sphere to be either night or day time.
		FOutputDeviceNull outputDevice;
		m_pcSkySphere->CallFunctionByNameWithArguments( TEXT( "UpdateSunDirection" ), outputDevice, nullptr, true );
	}
}

void ALevelManager::SetNewDay()
{
	// Increment the day ID as new day is set and set a new current day time type.
	m_iDayID++;
	m_eCurrentDayTimeType = m_aDayTypes[ m_iDayID ];

	// Change time to update the skysphere and villagers' and buildings' states.
	ChangeTime();
	m_pcPlayer->SetLocationToSpawn();
}

int ALevelManager::GetDayID() const										{ return m_iDayID; }

void ALevelManager::SetCurrentDayTimeType( EDayTimeType eDayTimeType )	{ m_eCurrentDayTimeType = eDayTimeType; }

EDayTimeType ALevelManager::GetCurrentDayTimeType() const				{ return m_eCurrentDayTimeType; }
