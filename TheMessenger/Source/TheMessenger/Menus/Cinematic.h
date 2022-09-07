// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TheMessenger/Endings/Struct_CinematicProperties.h"
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
	UPROPERTY( Category = "Properties", EditDefaultsOnly, BlueprintReadOnly, meta = ( DisplayName = "Accessed From Main Menu", AllowPrivateAccess = true ) )
		bool m_bAccessedFromMainMenu;

	UPROPERTY( meta = ( BindWidget ) )
		UTextBlock* SkipText;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY( BlueprintReadOnly, meta = ( BindWidget ) )
		UImage* CinematicImage;

public:
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable )
		void PlayCinematic( FCinematicProperties pfsEndingProperties );

	void SetAccessedFromMainMenu( bool bAccessedFromMainMenu );
};
