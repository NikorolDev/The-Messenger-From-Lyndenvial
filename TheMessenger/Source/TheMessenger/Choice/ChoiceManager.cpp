// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoiceManager.h"

#include <Components/BillboardComponent.h>
#include <Kismet/GameplayStatics.h>

#include "ChoiceSelectionWidget.h"
#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Interactable/Interactable_Base.h"

// Sets default values
AChoiceManager::AChoiceManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Billboard Component (m_pcIconBillboard).
	m_pcIconBillboard = CreateDefaultSubobject<UBillboardComponent>( TEXT( "Diaogue Manager Icon" ) );
	RootComponent = m_pcIconBillboard;
}


// Called when the game starts or when spawned
void AChoiceManager::BeginPlay()
{

	Super::BeginPlay();
	
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );

	m_pcDialogueManager->DialogueUpdate.AddDynamic( this, &AChoiceManager::DisplayChoices );

	m_pcChoiceSelectionWidget = CreateWidget<UChoiceSelectionWidget>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), m_tcChoiceSelectionWidget );
	m_pcChoiceSelectionWidget->SetChoiceManager( this );
	m_pcChoiceSelectionWidget->SetDialogueManager( m_pcDialogueManager );
	m_pcChoiceSelectionWidget->AddToViewport(1);
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
	
	// Display the choices and set visibility of the choice selection widget.
	m_pcChoiceSelectionWidget->CreateChoices( m_pfsChoices.Find( ChoiceID ) );
	m_pcChoiceSelectionWidget->SetVisibility( ESlateVisibility::Visible );
}

void AChoiceManager::AddChoices( AInteractable_Base* pcCharacterInteracted )
{
	UE_LOG( LogTemp, Display, TEXT( "[ADialogueManager::BeginPlay L.40] Choice added" ) );

	m_pcCharacterInteracted = pcCharacterInteracted;

	UE_LOG( LogTemp, Display, TEXT( "[ADialogueManager::BeginPlay L.40] %s" ), *m_pcCharacterInteracted->GetName() );
}

void AChoiceManager::UnHideChoices( FName& rnChoiceID )
{
	//FStructChoiceBranches* choiceBranch = m_pfsChoices.Find( rnChoiceID );
	//
	//choiceBranch->ChoiceBranches[0].
}
