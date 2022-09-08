// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

#include <Components/Image.h>
#include <Components/RichTextBlock.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Objectives/HintsManager.h"

void UPlayerHUD::NativeConstruct()
{
	// Call the UUserWidget native construct.
	Super::NativeConstruct();

	// Get hints manager from the level.
	m_pcHintsManager = Cast<AHintsManager>( UGameplayStatics::GetActorOfClass( GetWorld(), AHintsManager::StaticClass() ) );

	// Setup a delegate to be able to bind the function to it and to when the animation has finished.
	FWidgetAnimationDynamicEvent dObjectiveWidgetAnimation;

	// Bind the delegate to the function, which will be when the animation has finished.
	dObjectiveWidgetAnimation.BindDynamic( this, &UPlayerHUD::AnimationFinished );

	// Bind the animation to when its finished using the the delegate.
	BindToAnimationFinished( DisplayHint, dObjectiveWidgetAnimation );
}

void UPlayerHUD::DisplayHintPopUp()
{
	// Play the sound at 2D for the pop up.
	UGameplayStatics::PlaySound2D( GetWorld(), m_pcHintPopUpSound );
	
	// Set for animation to not play in reverse and then play it.
	m_bIsAnimationInReverse = false;
	PlayAnimation( DisplayHint );
}

void UPlayerHUD::SetHintUIElements( const FHintProperties& krfsHintProperties )
{
	// Check if the hint image is set
	if( krfsHintProperties.HintImage != nullptr )
	{
		// Display the hint image and set the texture of it
		HintIcon->SetVisibility( ESlateVisibility::Visible );
		HintIcon->SetBrushFromTexture( krfsHintProperties.HintImage, true );
	}
	else
	{
		// Otherwise, it will be collapsed and won't take up space for the text.
		HintIcon->SetVisibility( ESlateVisibility::Collapsed );
	}

	// Set the duration of the hint pop up for the timer and set the hint text.
	m_fHintPopUpDuration = krfsHintProperties.HintDuration;
	HintText->SetText( FText::FromString( krfsHintProperties.HintText ) );
}

void UPlayerHUD::ToggleBlackBackground( bool bIsVisible )
{
	// Check if it was set to be visible.
	if( bIsVisible )
	{
		// Make the black background visible.
		BlackBackground->SetVisibility( ESlateVisibility::Visible );
	}
	else
	{
		// Hide the black background from the screen.
		BlackBackground->SetVisibility( ESlateVisibility::Hidden );
	}
}

void UPlayerHUD::HideHintPopUp()
{
	// Hide hint by playing the animation in reverse
	m_bIsAnimationInReverse = true;
	PlayAnimationReverse( DisplayHint );
}

void UPlayerHUD::AnimationFinished()
{
	// Check if the animation was played in reverse.
	if( m_bIsAnimationInReverse )
	{
		// Do not display anymore hints.
		m_pcHintsManager->SetHintDisplay( false );
	}
	else
	{
		// Setup a timer handle that will delay the hiding of the tooltip off screen, based on the duration of tooltip display.
		FTimerHandle fsTimerHandle;
		GetWorld()->GetTimerManager().SetTimer( fsTimerHandle, this, &UPlayerHUD::HideHintPopUp, m_fHintPopUpDuration, false );
	}
}
