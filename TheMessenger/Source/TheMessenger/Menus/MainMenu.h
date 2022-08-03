// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

// Forward class declarations (Engine)
class UButton;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:

	UUserWidget* m_pcIntroCinematic;

	UPROPERTY( meta = ( BindWidget ) )
		UButton* NewGameButton;

	UPROPERTY( meta = ( BindWidget ) )
		UButton* ContinueButton;

	UPROPERTY( meta = ( BindWidget ) )
		UButton* QuitButton;

	UFUNCTION()
		void NewGameButtonClicked();

	UFUNCTION()
		void ContinueButtonClicked();

	UFUNCTION()
		void QuitButtonClicked();

protected:
	void NativeConstruct();

	UPROPERTY( Category = "Properties|Cutscene", EditDefaultsOnly, BlueprintReadWrite, meta = ( DisplayName = "Intro Cinematic Widget" ) )
		TSubclassOf<UUserWidget> m_tcIntroCinematic;

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void InitiateCinematic();

public:

	
};
