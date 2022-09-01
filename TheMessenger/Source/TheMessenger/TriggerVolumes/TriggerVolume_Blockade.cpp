// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_Blockade.h"

#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Dialogue/DialogueManager.h"

ATriggerVolume_Blockade::ATriggerVolume_Blockade()
	: m_bIsPassable (false)
	, m_nDialogueID ("")
{
}

void ATriggerVolume_Blockade::BeginPlay()
{
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );

	m_BoxTriggerVolume->OnComponentBeginOverlap.AddDynamic( this, &ATriggerVolume_Blockade::OnBeginOverlapTrigger );
}

void ATriggerVolume_Blockade::OnBeginOverlapTrigger( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	// Check if the actor is not another TriggerVolume_Dialogue and if the actor contains a tag of player.
	// This will detect the player if it has that tag.
	if( ( OtherActor != this ) && OtherActor->Tags.Contains( "Player" ) )
	{
		if( !m_bIsPassable )
		{
			m_pcDialogueManager->InitialiseDialogueSequence( m_nDialogueID );
		}
	}
}

void ATriggerVolume_Blockade::OnImpactActor_Implementation()
{
	m_bIsPassable = true;
	m_BoxTriggerVolume->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	m_VisualMesh->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}
