// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Character.h"

#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Dialogue/DialogueManager.h"


// Sets default values
AInteractable_Character::AInteractable_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInteractable_Character::BeginPlay()
{
	Super::BeginPlay();
	
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );
	
	m_pcDialogueManager->DialogueFinished.BindUObject( this, &AInteractable_Character::FollowPlayer );
}

// Called every frame
void AInteractable_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable_Character::OnInteract_Implementation( AActor* Caller )
{
	// When the player interacts with the character it will initialise the dialogue to play.
	m_pcDialogueManager->InitialiseDialogueSequence( m_nDialogueID );
}

void AInteractable_Character::OnFocus_Implementation()
{
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Green,
		TEXT( "On Focus" ) );
}

void AInteractable_Character::LostFocus_Implementation()
{
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
		TEXT( "Lost Focus" ) );
}
