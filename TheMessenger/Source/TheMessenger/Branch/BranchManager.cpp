// Fill out your copyright notice in the Description page of Project Settings.


#include "BranchManager.h"

#include <Components/BillboardComponent.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Interactable/Interactable_Base.h"

// Sets default values
ABranchManager::ABranchManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Billboard Component (m_pcIconBillboard).
	m_pcIconBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "Diaogue Manager Icon" ) );
	RootComponent = m_pcIconBillboard;
}

// Called when the game starts or when spawned
void ABranchManager::BeginPlay()
{
	Super::BeginPlay();

	// Get the game instance so that we can pass through the characters that were interacted that are not in the current level.
	//m_pcGameInstance = Cast<UTheMessengerGameInstance>( UGameplayStatics::GetGameInstance( GetWorld() ) );
}

// Called every frame
void ABranchManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABranchManager::SetNewDialogueID( FChoiceImpactProperties* krfsChoiceImpactProperties )
{
	if( krfsChoiceImpactProperties != nullptr )
	{
		krfsChoiceImpactProperties->CharacterAffectedTag->SetDialogueID( krfsChoiceImpactProperties->NewDialogueID );
	}
	else
	{
		//m_pcGameInstance->ChangeDialogueForCharacter();
	}
}
