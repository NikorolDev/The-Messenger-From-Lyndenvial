// Fill out your copyright notice in the Description page of Project Settings.


#include "Cinematic.h"

void UCinematic::NativeConstruct()
{
	// Calls the native construct from UUserWidget.
	Super::NativeConstruct();

	// Hide the widget.
	SetVisibility( ESlateVisibility::Hidden );
}

void UCinematic::SetAccessedFromMainMenu( bool bAccessedFromMainMenu ) { m_bAccessedFromMainMenu = bAccessedFromMainMenu; }
