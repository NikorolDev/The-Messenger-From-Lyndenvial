// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DayEndScreen.generated.h"

/**
 * 
 */
UCLASS()
class THEMESSENGER_API UDayEndScreen : public UUserWidget
{
	GENERATED_BODY()

private:

protected:
	virtual void NativeConstruct() override;

public:
	void DisplayScreen();
	
};
