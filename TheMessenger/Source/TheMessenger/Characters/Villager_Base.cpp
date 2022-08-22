// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager_Base.h"

#include <Components/AudioComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/WidgetComponent.h>
#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Dialogue/AmbientDialogueManager.h"
#include "CharacterOverHead.h"

// Sets default values
AVillager_Base::AVillager_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and setup...
	// Audio Component (m_pcAudioComponent).
	m_pcAudioComponent = CreateDefaultSubobject<UAudioComponent>( TEXT( "Audio Component" ) );
	m_pcAudioComponent->SetupAttachment( GetCapsuleComponent() );

	// Widget Component (m_pcWidgetComponent).
	m_pcWidgetComponent = CreateDefaultSubobject<UWidgetComponent>( TEXT( "Widget Component" ) );
	m_pcWidgetComponent->SetupAttachment( GetCapsuleComponent() );
}

// Called when the game starts or when spawned
void AVillager_Base::BeginPlay()
{
	Super::BeginPlay();

	m_pcAmbientDialogueManager = Cast <AAmbientDialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), AAmbientDialogueManager::StaticClass() ) );

	m_pcCharacterOverHead = Cast<UCharacterOverHead>( m_pcWidgetComponent->GetWidget() );	
}

void AVillager_Base::PlayAmbientDialogueSequence( FString& krsDialogueText, USoundWave* pcDialogueAudio )
{
	if( pcDialogueAudio )
	{
		UGameplayStatics::PlaySoundAtLocation( GetWorld(), pcDialogueAudio, GetActorLocation() );
	}

	m_pcCharacterOverHead->DisplayText( krsDialogueText );
}

UCharacterOverHead& AVillager_Base::GetCharatcerOverHead() const
{
	return *m_pcCharacterOverHead;
}

void AVillager_Base::OnFocus_Implementation()
{
	m_pcCharacterOverHead->ToggleOnFocusOverlayVisibility( true, m_bIsInteractable );
	UE_LOG( LogTemp, Warning,
		TEXT( "On Focus" ) );
}

void AVillager_Base::LostFocus_Implementation()
{
	m_pcCharacterOverHead->ToggleOnFocusOverlayVisibility( false );
	UE_LOG( LogTemp, Warning,
		TEXT( "Off Focus" ) );
}

