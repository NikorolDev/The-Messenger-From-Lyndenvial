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
	// The icon that is used to display along side the tooltip.
	UPROPERTY( meta = ( BindWidget ) )
		UImage* HintIcon;

	UPROPERTY( meta = ( BindWidget ) )
		URichTextBlock* HintText;

	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
		UWidgetAnimation* DisplayHint;

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

	void SetHintUIElements( const FHintProperties& krfsHintProperties );

};
