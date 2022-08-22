// Fill out your copyright notice in the Description page of Project Settings.


#include "AmbientDialogueManager.h"

// Sets default values
AAmbientDialogueManager::AAmbientDialogueManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAmbientDialogueManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAmbientDialogueManager::SetDialogueTerm()
{
	if( m_iDialogueID < m_iNumberOfDialogueTerms )
	{
		FAmbientDialogueProperties* fsAmbientDialogueTerm = &m_pfsDialogueSequence->AmbientDialogueSequence[ m_iDialogueID ];


	}
}

void AAmbientDialogueManager::InitialiseDialogueSequence( const FName& rnDialogueID )
{
	if( !m_bIsDialogueSequenceInitialised )
	{
		m_iDialogueID = 0;
		m_fDialogueTermTime = 0;
		m_pfsDialogueSequence = m_tmDialogueTable.Find( rnDialogueID );

		if( m_pfsDialogueSequence )
		{
			m_bIsDialogueSequenceInitialised = true;

			m_iNumberOfDialogueTerms = m_pfsDialogueSequence->AmbientDialogueSequence.Num();


		}
	}
}
