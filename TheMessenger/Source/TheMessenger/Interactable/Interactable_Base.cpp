// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Base.h"

#include "TheMessenger/Dialogue/DialogueManager.h"

// Sets default values
AInteractable_Base::AInteractable_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable_Base::OnInteract_Implementation( AActor* Caller )
{
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Green,
		TEXT( "Interacted" ) );
}

void AInteractable_Base::OnFocus_Implementation()
{
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Green,
		TEXT( "On Focus" ) );
}

void AInteractable_Base::LostFocus_Implementation()
{
	GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red,
		TEXT( "Lost Focus" ) );
}

