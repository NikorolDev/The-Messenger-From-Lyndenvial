// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cinematic.generated.h"

// Forward class declarations (Engine)
class UImage;
class UMaterialInstance;
class UMediaPlayer;
class UTextBlock;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API UCinematic : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* SkipText;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY( BlueprintReadOnly, meta = ( BindWidget ) )
		UImage* CinematicImage;

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void SkipCinematic();
public:

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void PlayCinematic( UMaterialInstance* CinematicMaterial, UMediaPlayer* CinematicPlayer );
};
