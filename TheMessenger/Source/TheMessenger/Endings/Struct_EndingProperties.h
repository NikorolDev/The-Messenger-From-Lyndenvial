#pragma once

#include "Struct_EndingProperties.generated.h"

// Forward class declarations (Engine)
class UMaterialInstance;
class UMediaPlayer;
class USoundWave;

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FEndingProperties
// Author				: Nikodem Hamrol
// Purpose				: This struct is made to store the properties of each ending. It contains the video and the sound.
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FEndingProperties
{
	GENERATED_BODY()

	// The material of the cinematic to be shown on the widget.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		UMaterialInstance*	CinematicMaterial = nullptr;

	// The player that will play the cinematic.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		UMediaPlayer*		CinematicPlayer = nullptr;

	// The sound of the cinematic.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		USoundWave*			CinematicSound = nullptr;
};