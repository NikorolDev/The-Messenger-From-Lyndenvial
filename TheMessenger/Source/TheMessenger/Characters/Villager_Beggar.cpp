// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_Beggar.h"

#include "TheMessenger/Level/LevelManager.h"


AVillager_Beggar::AVillager_Beggar()
	: m_bhasHelped(true)
{
}

void AVillager_Beggar::BeginPlay()
{
	AVillager_Base::BeginPlay();
}

void AVillager_Beggar::OnImpactActor_Implementation()
{
	if( GetLevelManager().GetDayID() == m_iDayToAppear )
	{
		if( m_bhasHelped )
		{
			HideCharacter( false );
		}
	}
	else
	{
		HideCharacter( true );
	}
}

void AVillager_Beggar::SetHasHelped( bool bHasHelped ) { m_bhasHelped = bHasHelped; }
