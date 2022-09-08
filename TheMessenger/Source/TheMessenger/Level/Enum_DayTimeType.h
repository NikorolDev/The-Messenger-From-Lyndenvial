#pragma once

#include "CoreMinimal.h"
#include "Enum_DayTimeType.generated.h"

// The time types within the day.
UENUM( BlueprintType )
enum class EDayTimeType : uint8
{
	Day,
	Night
};
