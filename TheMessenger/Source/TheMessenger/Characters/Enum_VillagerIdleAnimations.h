#pragma once

#include "CoreMinimal.h"
#include "Enum_VillagerIdleAnimations.generated.h"

// An enum class of the animations and poses to be set on characters.
UENUM( BlueprintType )
enum class EVillagerIdleAnimations : uint8
{
	FemaleStanding,
	MaleStanding,
	GuardStanding,
	MaleHandsBackStanding,
};
