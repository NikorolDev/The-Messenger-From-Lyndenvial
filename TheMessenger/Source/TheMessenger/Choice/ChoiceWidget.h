// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct_Choice.h"
#include "ChoiceWidget.generated.h"

class UButton;
class URichTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FChoiceSelectedSignature, const FName&, ChoiceID );

/**
 * 
 */
UCLASS()
class THEMESSENGER_API UChoiceWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	FName* m_pnAssignedChoiceID;

	UPROPERTY( meta = ( BindWidget ) )
		UButton* ChoiceButton;

	UPROPERTY( meta = ( BindWidget ) )
		URichTextBlock* ChoiceText;

	UFUNCTION()
		void OnButtonClicked();

protected:
	//-----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: NativeConstruct() override
	// Author			: Unreal Engine 4
	// Editors			: Nikodem Hamrol
	// Purpose			: This is the constructor to the widget, which is similar to the "Event Construct" in Blueprint Widget.
	//					,	It is used to hide itself when starting the game.
	//-----------------------------------------------------------------------------------------------------------------------------
		virtual void NativeConstruct() override;

public:
	
	UPROPERTY( BlueprintAssignable, BlueprintCallable )
		FChoiceSelectedSignature ChoiceSelected;

	void SetButtonText( int ChoiceCount, const FString& ChoiceDisplayText, FName& rnDialogueID );


};
