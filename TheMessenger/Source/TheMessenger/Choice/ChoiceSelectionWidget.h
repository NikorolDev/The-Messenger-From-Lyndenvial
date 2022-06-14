// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct_Choice.h"
#include "ChoiceSelectionWidget.generated.h"

class UChoiceWidget;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API UChoiceSelectionWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY( meta = ( BindWidget ) )
		UVerticalBox* ChoiceBox;

	TArray<UChoiceWidget*> m_aChoiceWidgets;

protected:

	UPROPERTY( Category = Widgets, EditDefaultsOnly, BlueprintReadOnly )
		TSubclassOf<UChoiceWidget> m_tcChoiceWidget;

	virtual void NativeConstruct() override;

public:
	void CreateChoices( FStructChoiceBranches* pfsChoiceBranches );
};
