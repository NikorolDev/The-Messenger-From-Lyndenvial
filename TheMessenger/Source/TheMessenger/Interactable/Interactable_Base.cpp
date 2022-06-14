// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Base.h"

#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Choice/ChoiceManager.h"
#include "TheMessenger/Dialogue/DialogueManager.h"

// Sets default values
AInteractable_Base::AInteractable_Base()
	: m_nDialogueID( "" )
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInteractable_Base::BeginPlay()
{
	Super::BeginPlay();
	
	m_pcChoiceManager = Cast<AChoiceManager>( UGameplayStatics::GetActorOfClass( GetWorld(), AChoiceManager::StaticClass() ) );


	// Get the dialogue manager that is in the level.
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );

	// Check if the dialogue manager was retrieved, which otherwise will print an error log
	if( !m_pcDialogueManager )
	{
		// Log that the dialogue manager is missing.
		UE_LOG( LogTemp, Error,
			TEXT( "MISSING DIALOGUE MANAGER IN THE LEVEL | DIALOGUE WILL NOT INITIALISE | ADD DIALOGUE MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/DIALOGUE" ) );
		GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
			TEXT( "MISSING DIALOGUE MANAGER IN THE LEVEL | DIALOGUE WILL NOT INITIALISE | ADD DIALOGUE MANAGER TO THE LEVEL UNDER 'C++CLASSES/RADIANCE/DIALOGUE" ) );
	}


}

// Called every frame
void AInteractable_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable_Base::OnInteract_Implementation( AActor* Caller )
{
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Green,
		TEXT( "Interacted" ) );

	m_pcChoiceManager->AddChoices( this );
	m_pcDialogueManager->InitialiseDialogueSequence( m_nDialogueID );
}

void AInteractable_Base::OnFocus_Implementation()
{
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Green,
		TEXT( "On Focus" ) );
}

void AInteractable_Base::LostFocus_Implementation()
{
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
		TEXT( "Lost Focus" ) );
}

FStructChoiceBranches* AInteractable_Base::GetChoicesFromID( const FName& ChoiceID )
{
	auto test = m_pfsChoices.Find( ChoiceID );
	return test;
}

