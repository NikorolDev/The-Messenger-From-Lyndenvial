#pragma once

#include "Struct_CinematicProperties.generated.h"

// Forward class declarations (Engine)
class UFileMediaSource;
class UMaterialInstance;
class UMediaPlayer;
class USoundWave;

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FCinematicProperties
// Author				: Nikodem Hamrol
// Purpose				: This struct is made to store the properties of each ending. It contains the video and the sound.
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FCinematicProperties
{
	GENERATED_BODY()

	// The day that ending will trigger.
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
		int					DayToTrigger		= 0;

	// The source of the cinematic to play.
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
		UFileMediaSource*	CinematicSource		= nullptr;

	// The material of the cinematic to be shown on the widget.
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
		UMaterialInstance*	CinematicMaterial	= nullptr;

	// The player that will play the cinematic.
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
		UMediaPlayer*		CinematicPlayer		= nullptr;

	// The sound of the cinematic.
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
		USoundWave*			CinematicSound		= nullptr;
};