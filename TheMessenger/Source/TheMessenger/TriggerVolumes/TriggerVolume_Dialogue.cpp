// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_Dialogue.h"

#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Dialogue/DialogueManager.h"

void ATriggerVolume_Dialogue::BeginPlay()
{
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );

	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_Dialogue::OnBeginOverlapTrigger );
}

void ATriggerVolume_Dialogue::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	// Check if the actor is not another TriggerVolume_Dialogue and if the actor contains a tag of player.
	// This will detect the player if it has that tag.
	if( ( OtherActor != this ) && OtherActor->Tags.Contains( "Player" ) )
	{
		int iDialogueID = FMath::RandRange( 0, m_aDialogueIDs.Num()-1 );

		m_pcDialogueManager->InitialiseDialogueSequence( m_aDialogueIDs[ iDialogueID ] );
	}
}
