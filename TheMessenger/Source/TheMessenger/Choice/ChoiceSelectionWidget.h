// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Struct_Choice.h"
#include "ChoiceSelectionWidget.generated.h"

class UChoiceWidget;
class UVerticalBox;

class ADialogueManager;

/**
 * 
 */
UCLASS()
class THEMESSENGER_API UChoiceSelectionWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	ADialogueManager* m_pcDialogueManager;

	TArray<UChoiceWidget*> m_aChoiceWidgets;

	UPROPERTY( meta = ( BindWidget ) )
		UVerticalBox* ChoiceBox;

	UFUNCTION()
		void OnChoiceSelected(const FName& rnDialogueID );

protected:

	UPROPERTY( Category = Widgets, EditDefaultsOnly, BlueprintReadOnly )
		TSubclassOf<UChoiceWidget> m_tcChoiceWidget;

	virtual void NativeConstruct() override;

public:
	void CreateChoices( FStructChoiceBranches* pfsChoiceBranches );

	void SetDialogueManager(ADialogueManager* pcDialogueManager);
};
