// Fill out your copyright notice in the Description page of Project Settings.


#include "Entrance_Door.h"

#include "Interactable_Character.h"

// Sets default values
AEntrance_Door::AEntrance_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEntrance_Door::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntrance_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEntrance_Door::OnInteract_Implementation( AActor* Caller )
{
	// Interact with the character when interacting with the door.
	m_pcCharacterTointeract->OnInteract_Implementation( this );
}
