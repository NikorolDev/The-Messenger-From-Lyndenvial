// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	// Setup a delegate to be able to bind the function to it and to when the animation has finished.
	FWidgetAnimationDynamicEvent dObjectiveWidgetAnimation;

	// Bind the delegate to the function, which will be when the animation has finished.
	dObjectiveWidgetAnimation.BindDynamic( this, &UPlayerHUD::AnimationFinished );

	// Bind the animation to when its finished using the the delegate.
	BindToAnimationFinished( DisplayObjective, dObjectiveWidgetAnimation );
}

void UPlayerHUD::AnimationFinished()
{
}
