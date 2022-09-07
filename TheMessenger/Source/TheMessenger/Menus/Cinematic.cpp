// Fill out your copyright notice in the Description page of Project Settings.


#include "Cinematic.h"

void UCinematic::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility( ESlateVisibility::Hidden );
}

void UCinematic::SetAccessedFromMainMenu( bool bAccessedFromMainMenu ) { m_bAccessedFromMainMenu = bAccessedFromMainMenu; }
