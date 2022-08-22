// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_Base.h"

#include <Components/AudioComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Dialogue/AmbientDialogueManager.h"

// Sets default values
AVillager_Base::AVillager_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AVillager_Base::PlayAmbientDialogueSequence()
{
}

// Called when the game starts or when spawned
void AVillager_Base::BeginPlay()
{
	Super::BeginPlay();

	m_pcAmbientDialoguemanager = Cast <AAmbientDialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), AAmbientDialogueManager::StaticClass() ) );

	//m_pcDialogueWidget = Cast<UDialogueWidgetHUD>( m_pcWidgetComponent->GetWidget() );
	
}
