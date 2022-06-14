// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoiceManager.h"

#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Dialogue/DialogueManager.h"

// Sets default values
AChoiceManager::AChoiceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void AChoiceManager::BeginPlay()
{
	Super::BeginPlay();
	
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );

	m_pcDialogueManager->DialogueUpdate.AddDynamic( this, &AChoiceManager::DisplayChoices );
}

// Called every frame
void AChoiceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChoiceManager::DisplayChoices(FName ChoiceID)
{
	UE_LOG( LogTemp, Display, TEXT( "[ADialogueManager::BeginPlay L.38] Choice Displayed" ) );
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Green, TEXT( "Choice Displayed" ) );
}

void AChoiceManager::AddChoices( FStructChoiceBranches* tmChoices )
{
	UE_LOG( LogTemp, Display, TEXT( "[ADialogueManager::BeginPlay L.40] Choice added" ) );

	m_fsChoiceBranch = tmChoices;
}

void AChoiceManager::UnloadChoices()
{
}
