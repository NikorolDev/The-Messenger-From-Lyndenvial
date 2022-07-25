// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InfluentiableThroughTimeType.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInfluentiableThroughTimeType : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE( FOnFinishedSettingSignature )

/**
 * 
 */
class THEMESSENGER_API IInfluentiableThroughTimeType
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 
	FOnFinishedSettingSignature OnFinishedSetting;

	// 
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent )
		void SetForNextDay();
};
