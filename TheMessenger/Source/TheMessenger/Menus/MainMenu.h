// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheMessenger/Endings/Struct_CinematicProperties.h"
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

	UPROPERTY( Category = "Properties", EditAnywhere, meta = ( DisplayName = "Intro Cinematic" ) )
		FCinematicProperties m_pfsIntroCinematic;

	UPROPERTY( Category = "Properties|Widget", EditDefaultsOnly, meta = ( DisplayName = "Cinematic Widget" ) )
		TSubclassOf<UCinematic> m_tcCinematicWidget;

	UPROPERTY( meta = ( BindWidget ) )
		UButton* NewGameButton;

	UPROPERTY( meta = ( BindWidget ) )
		UButton* QuitButton;

	UFUNCTION()
		void NewGameButtonClicked();

	UFUNCTION()
		void QuitButtonClicked();

protected:
	virtual void NativeConstruct() override;
};
