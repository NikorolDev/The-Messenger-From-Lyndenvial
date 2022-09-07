// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheMessenger/Objectives/Struct_HintProperties.h"
#include "PlayerHUD.generated.h"

// Forward class declarations (Engine)
class UImage;
class URichTextBlock;
class UWidgetAnimation;
class USoundWave;

// Forward class declarations (Game)
class AHintsManager;

//-----------------------------------------------------------------------------------------------------------------------------
// Class Name			: UPlayerHUD
// Author				: Nikodem Hamrol
// Inherits				: UUserWidget
// Purpose				: Class to handle HUD elements displayed on screen.
//-----------------------------------------------------------------------------------------------------------------------------
UCLASS()
class THEMESSENGER_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	// Is the animation playing is reverse or normally, to play the animation properly.
	bool m_bIsAnimationInReverse;

	// The duration of the hint displayed.
	float m_fHintPopUpDuration;

	// The hint manager to disable hint display to allow for the hint to be redisplayed.
	AHintsManager* m_pcHintsManager;

	// Sound that plays when a hint pops up
	UPROPERTY( Category = "Properties|Sounds", EditDefaultsOnly, BlueprintReadOnly, meta = ( DisplayName = "Hint Pop Up Sound", AllowPrivateAccess = true ) )
		USoundWave* m_pcHintPopUpSound;

	// The black background that covers the whole screen.
	UPROPERTY( meta = ( BindWidget ) )
		UImage* BlackBackground;

	// The icon that is used to display along side the tooltip.
	UPROPERTY( meta = ( BindWidget ) )
		UImage* HintIcon;

	// 
	UPROPERTY( meta = ( BindWidget ) )
		URichTextBlock* HintText;

	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
		UWidgetAnimation* DisplayHint;

	void HideHintPopUp();

	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: AnimationFinished()
	// Author				: Nikodem Hamrol
	// Purpose				: A callback function that will be triggered when aniamtion is finished, which will...
	//-----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void AnimationFinished();

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name		: NativeConstruct
	// Author				: UE4
	// Editor				: Nikodem Hamrol
	// Purpose				: The contrustor of the PlayerHUD that will setup delegates and...
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual void NativeConstruct() override;

public:

	void DisplayHintPopUp();

	void SetHintUIElements( const FHintProperties& krfsHintProperties );

	UFUNCTION( BlueprintCallable )
		void ToggleBlackBackground( bool bIsVisible );
};
