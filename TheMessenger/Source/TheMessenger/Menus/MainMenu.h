// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

// Forward class declarations (Engine)
class UButton;
class UMaterialInstance;
class UMediaPlayer;

// Forward class declarations (Game)
class UCinematic;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

private:

	UCinematic* m_pcCinematicWidget;

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
	virtual void NativeConstruct() override;

	UPROPERTY( Category = "Properties|Intro Cinematic", EditDefaultsOnly, BlueprintReadOnly, meta = ( DisplayName = "Intro Cinematic Player" ) )
		UMaterialInstance* m_pcIntroCinematicMaterial;

	UPROPERTY( Category = "Properties|Intro Cinematic", EditDefaultsOnly, BlueprintReadOnly, meta = ( DisplayName = "Intro Cinematic Player" ) )
		UMediaPlayer* m_pcIntroCinematicPlayer;

	UPROPERTY( Category = "Properties|Widget", EditDefaultsOnly, BlueprintReadOnly, meta = ( DisplayName = "Cinematic Widget" ) )
		TSubclassOf<UCinematic> m_tcCinematicWidget;

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void InitiateCinematic();

public:

	
};
