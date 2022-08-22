// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"

#include <Components/BillboardComponent.h>
#include <Engine/DirectionalLight.h>
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>
#include <Misc/OutputDeviceNull.h>

#include "Building_Base.h"
#include "TheMessenger/Interactable/Interactable_Character.h"

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
	for( int i = 0; i < m_aChangers.Num(); ++i )
	{
		m_aChangers[ i ]->SetForNextDay(m_aDayTypes[DayID]);
	}

	if( m_pcSkyLightSource )
	{
		m_pcSkyLightSource->SetActorRotation(FRotator());
	}

	if( m_pcSkySphere )
	{
		FOutputDeviceNull outputDevice;
		m_pcSkySphere->CallFunctionByNameWithArguments( TEXT( "UpdateSunDirection" ), outputDevice, nullptr, true );
	}
}

void ALevelManager::SetManagersToCharacters()
{
	// Loop through all main characters in the level and set their new dialogue manager to grab their dialogue from.
	for( int iCharacterID = 0; iCharacterID < m_apcMainCharacters.Num(); ++iCharacterID )
	{
		// Set the new dialogue manager for the main character.
		m_apcMainCharacters[ iCharacterID ]->SetDialogueManager( m_apcDialogueManagers[ DayID ] );
	}
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();

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
	SetManagersToCharacters();

	SetNewDay();
}

ADialogueManager& ALevelManager::GetCurrentDialogueManager() const { return *m_apcDialogueManagers[ DayID ]; }
