#pragma once

#include "Struct_HintProperties.generated.h"

// Forward class declaration
class UTexture2D;

//----------------------------------------------------------------------------------------------------------------------------
// Struct Name			: FHintProperties
// Author				: Nikodem Hamrol
// Purpose				: This struct is made to store the properties of each hint, such as text, duration display on
//						,	screen and the icon to help with finding what they are looking for.	
//----------------------------------------------------------------------------------------------------------------------------
USTRUCT( BlueprintType )
struct FHintProperties
{
	GENERATED_BODY()

	// The image icon of the objective.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		UTexture2D* HintImage = nullptr;

	// The text to display of the objective.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		FString		HintText = FString( "" );

	// The extra time to delay the next dialogue term playing.
	UPROPERTY( EditInstanceOnly, BlueprintReadOnly )
		float		HintDuration = 0.0f;
};
