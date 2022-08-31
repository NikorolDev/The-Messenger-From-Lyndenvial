// Fill out your copyright notice in the Description page of Project Settings.


#include "DayEndScreen.h"

void UDayEndScreen::NativeConstruct()
{
	SetVisibility( ESlateVisibility::Hidden );
}

void UDayEndScreen::DisplayScreen()
{
	SetVisibility( ESlateVisibility::Visible );
}
