// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_Beggar.h"

#include <Components/BoxComponent.h>

#include "TheMessenger/Level/LevelManager.h"
#include "TheMessenger/TriggerVolumes/TriggerVolume_Sequence.h"


AVillager_Beggar::AVillager_Beggar()
	: m_bhasHelped(true)
{
}

void AVillager_Beggar::OnImpactActor_Implementation()
{
	// Get the day ID from the level maanger and check if it is the same as the day to appear.
	if( GetLevelManager().GetDayID() == m_iDayToAppear )
	{
		// Check if the beggar has been helped.
		if( m_bhasHelped )
		{
			// Unhide the beggar and set collision of the trigger box to be query only.
			HideCharacter( false );
			m_pcTriggerVolumeAssigned->GetTriggerBox().SetCollisionEnabled( ECollisionEnabled::QueryOnly );
		}
		else
		{
			// hide the beggar and disable collision of the box trigger.
			HideCharacter( true );
			m_pcTriggerVolumeAssigned->GetTriggerBox().SetCollisionEnabled( ECollisionEnabled::NoCollision );
		}
	}
	else
	{
		// Keep character hidden.
		HideCharacter( true );
	}
}

void AVillager_Beggar::SetHasHelped( bool bHasHelped ) { m_bhasHelped = bHasHelped; }
