// Fill out your copyright notice in the Description page of Project Settings.


#include "ChoiceWidget.h"

#include <Components/RichTextBlock.h>

void UChoiceWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UChoiceWidget::SetButtonText( int ChoiceCount, const FString& ChoiceDisplayText )
{
	ChoiceText->SetText( FText::FromString( FString::FromInt( ChoiceCount ) + ". " + ChoiceDisplayText));
}
