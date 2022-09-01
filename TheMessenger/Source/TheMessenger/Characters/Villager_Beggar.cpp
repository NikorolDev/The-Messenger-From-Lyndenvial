// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_Beggar.h"

void AVillager_Beggar::BeginPlay()
{
	AVillager_Base::BeginPlay();

	m_v3InitialLocation = GetActorLocation();
}

void AVillager_Beggar::OnImpactActor_Implementation()
{
	SetActorLocation( m_v3OffMapLocation );
}
