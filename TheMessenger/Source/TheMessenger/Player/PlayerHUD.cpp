// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include <Components/Image.h>
#include <Components/RichTextBlock.h>

#include "TheMessenger/Objectives/HintsManager.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup a delegate to be able to bind the function to it and to when the animation has finished.
	FWidgetAnimationDynamicEvent dObjectiveWidgetAnimation;

	// Bind the delegate to the function, which will be when the animation has finished.
	dObjectiveWidgetAnimation.BindDynamic( this, &UPlayerHUD::AnimationFinished );

	// Bind the animation to when its finished using the the delegate.
	BindToAnimationFinished( DisplayHint, dObjectiveWidgetAnimation );
}

void UPlayerHUD::DisplayHintPopUp()
{
	m_bIsAnimationInReverse = false;
	PlayAnimation( DisplayHint );
}

void UPlayerHUD::SetHintUIElements( const FHintProperties& krfsHintProperties )
{
	if( krfsHintProperties.HintImage != nullptr )
	{
		HintIcon->SetVisibility( ESlateVisibility::Visible );
		HintIcon->SetBrushFromTexture( krfsHintProperties.HintImage, true );
	}
	else
	{
		HintIcon->SetVisibility( ESlateVisibility::Collapsed );
	}

	m_fHintPopUpDuration = krfsHintProperties.HintDuration;
	HintText->SetText( FText::FromString( krfsHintProperties.HintText ) );
}

void UPlayerHUD::HideHintPopUp()
{
	m_bIsAnimationInReverse = true;
	PlayAnimationReverse( DisplayHint );
}

void UPlayerHUD::AnimationFinished()
{
	if( m_bIsAnimationInReverse )
	{
		m_pcHintsManager->SetHintDisplay( false );
	}
	else
	{
		// Setup a timer handle that will delay the hiding of the tooltip off screen, based on the duration of tooltip display.
		FTimerHandle fsTimerHandle;

		GetWorld()->GetTimerManager().SetTimer( fsTimerHandle, this, &UPlayerHUD::HideHintPopUp, m_fHintPopUpDuration, false );
	}
}
