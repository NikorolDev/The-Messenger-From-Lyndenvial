#pragma once

#include "CoreMinimal.h"
#include "Enum_VillagerIdleAnimations.generated.h"

UENUM( BlueprintType )
enum class EVillagerIdleAnimations : uint8
{
	FemaleStanding,
	MaleStanding,
	GuardStanding,
	MaleHandsBackStanding,
};
