// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DayEndScreen.generated.h"

class UButton;
class UTextBlock;

class ALevelManager;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API UDayEndScreen : public UUserWidget
{
	GENERATED_BODY()

private:
	int m_iDayNumber;

	ALevelManager* m_pcLevelManager;

	UPROPERTY( meta = ( BindWidget ) )
		UButton* MainMenu;

	UPROPERTY( meta = ( BindWidget ) )
		UButton* Continue;

	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* DayComplete;

	UFUNCTION()
		void OnContinueClicked();

	UFUNCTION()
		void OnMainMenuClicked();

protected:
	virtual void NativeConstruct() override;

public:
	void DisplayScreen();	
};
