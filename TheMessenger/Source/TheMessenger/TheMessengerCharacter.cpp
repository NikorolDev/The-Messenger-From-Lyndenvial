// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheMessengerCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include <DrawDebugHelpers.h>

#include <Kismet/GameplayStatics.h>

#include "TheMessenger/Dialogue/DialogueManager.h"
#include "TheMessenger/Interactable/InteractableInterface.h"
#include "TheMessenger/Player/PlayerHUD.h"

//////////////////////////////////////////////////////////////////////////
// ATheMessengerCharacter


ATheMessengerCharacter::ATheMessengerCharacter()
	:m_fLineTraceDistance (1000.0f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATheMessengerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction( "Interact", IE_Pressed, this, &ATheMessengerCharacter::OnInteractPressed );

	PlayerInputComponent->BindAxis("MoveForward", this, &ATheMessengerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATheMessengerCharacter::MoveRight);

	// "turn" handles devices that provide an absolute delta, such as a mouse.
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void ATheMessengerCharacter::BeginPlay()
{
	// Call the Actor's begin play.
	Super::BeginPlay();

	// Get the player's location and rotation.
	m_v3SpawnLocation = GetActorLocation();
	m_v3SpawnRotation = GetActorRotation();

	// Get dialogue manager and the player controller.
	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );
	m_pcPlayerController = Cast<APlayerController>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ) );

	// Create the player HUD widget and add it to the viewport.
	m_pcPlayerHUD = CreateWidget<UPlayerHUD>( m_pcPlayerController, m_tcPlayerHUD );
	m_pcPlayerHUD->AddToViewport(-1);

	// Bind the function on dialogue finished to set the player back from sequence.
	m_pcDialogueManager->DialogueFinished.AddUObject( this, &ATheMessengerCharacter::SetPlayerBackFromSequence );
}


void ATheMessengerCharacter::Tick( float DeltaTime )
{
	// Create a new line trace pre tick.
	TraceForward();
}

void ATheMessengerCharacter::TraceForward()
{
	// Create all necessary values needed to create the line trace.
	FHitResult OutHit;
	FVector v3StartPosition = FollowCamera->GetComponentLocation();
	FVector v3Forward		= FollowCamera->GetForwardVector();
	FVector v3EndPosition	= v3StartPosition + ( v3Forward * m_fLineTraceDistance );
	FCollisionQueryParams CollisionParams;

	// Trace a line and check if it has hit something.
	bool bHit = GetWorld()->LineTraceSingleByChannel( OutHit, v3StartPosition, v3EndPosition, ECC_Visibility, CollisionParams );
	if( bHit )
	{
		// Get the actor detected from the hit result.
		AActor* ActorDetected = OutHit.GetActor();

		// Check if the actor is not nullptr.
		if( ActorDetected )
		{
			// If actor detected is not the same as the currently focused actor.
			if( ActorDetected != m_pcFocusedActor )
			{
				// Check if the focused actor is not nullptr.
				if( m_pcFocusedActor )
				{
					// Cast the focused actor to an interactable interface. Then check if it is not a nullptr.
					IInteractableInterface* InteractableActor = Cast<IInteractableInterface>( m_pcFocusedActor );
					if( InteractableActor )
					{
						// The interactable has now lost focused.
						InteractableActor->LostFocus_Implementation();
					}
				}

				// Cast the actor detected to be an interactable.
				IInteractableInterface* InteractableActor = Cast<IInteractableInterface>( ActorDetected );
				if( InteractableActor )
				{
					// The interactable actor is now focused.
					InteractableActor->OnFocus_Implementation();
				}
				// Set the focused actor to be the actor detected.
				m_pcFocusedActor = ActorDetected;
			}
		}
		else
		{
			// Check if the focused actor is not a nullptr
			if( m_pcFocusedActor )
			{
				// Cast it as an interactable and if it is not a nullptr.
				IInteractableInterface* InteractableActor = Cast<IInteractableInterface>( m_pcFocusedActor );
				if( InteractableActor )
				{
					// Lose focus of the interactable.
					InteractableActor->LostFocus_Implementation();
				}
			}
			// Set the focused actor to be nullptr.
			m_pcFocusedActor = nullptr;
		}
	}
	else
	{
		// Check if the focused actor is not a nullptr
		if( m_pcFocusedActor )
		{
			// Cast it as an interactable and if it is not a nullptr.
			IInteractableInterface* InteractableActor = Cast<IInteractableInterface>( m_pcFocusedActor );
			if( InteractableActor )
			{
				// Lose focus of the interactable.
				InteractableActor->LostFocus_Implementation();
			}
		}
		// Set the focused actor to be nullptr.
		m_pcFocusedActor = nullptr;
	}
}

void ATheMessengerCharacter::OnInteractPressed()
{
	// Check if the player is focusing on an interactable actor.
	if( m_pcFocusedActor )
	{
		// Cast the focused to an interactrable,
		IInteractableInterface* Interactable = Cast<IInteractableInterface>( m_pcFocusedActor );

		// Check if the interactable is not nullptr;
		if( Interactable )
		{
			// Interact with the actor.
			Interactable->OnInteract_Implementation( m_pcFocusedActor );
		}
	}
}

void ATheMessengerCharacter::SetPlayerBackFromSequence()
{
	// Check if is not in an end day sequenece.
	if( !m_bInEndDaySequence )
	{
		// Enable input for the controller and set the input on game only and hide the mouse cursor.
		EnableInput( m_pcPlayerController );
		m_pcPlayerController->SetInputMode( FInputModeGameOnly() );
		m_pcPlayerController->bShowMouseCursor = false;
	}

	// Unlock movement.
	m_bIsMovementLocked = false;
}

void ATheMessengerCharacter::SetPlayerForSequence( const FVector& v3PlayerPosition, float PlayerRotationYaw )
{
	// Lock the movement and disable input.
	m_bIsMovementLocked = true;
	DisableInput( m_pcPlayerController );

	// Set the location and rotation of the player to be infornt of the villager.
	SetActorLocation( v3PlayerPosition );
	m_pcPlayerController->SetControlRotation( FRotator( 0, PlayerRotationYaw, 0 ) );
}


void ATheMessengerCharacter::SetLocationToSpawn()
{
	// When the player is reset on the next day, it will not be in an end day sequence.
	m_bInEndDaySequence = false;

	// Set location and rotation of the player on the spawn values.
	SetActorLocation( m_v3SpawnLocation );
	m_pcPlayerController->SetControlRotation( m_v3SpawnRotation );

	// Set input mode to be game only, hide mouse cursor, and enable input.
	m_pcPlayerController->SetInputMode( FInputModeGameOnly() );
	m_pcPlayerController->bShowMouseCursor = false;
	EnableInput( m_pcPlayerController );
}

void ATheMessengerCharacter::SetInEndDaySequence( bool bInEndDaySequence )	{ m_bInEndDaySequence = bInEndDaySequence; }

UPlayerHUD* ATheMessengerCharacter::GetPlayerHUD()							{ return m_pcPlayerHUD; }

APlayerController& ATheMessengerCharacter::GetPlayerController() const		{ return *m_pcPlayerController; }

void ATheMessengerCharacter::TurnAtRate( float Rate )
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput( Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() );
}

void ATheMessengerCharacter::LookUpAtRate( float Rate )
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput( Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() );
}

void ATheMessengerCharacter::MoveForward(float Value)
{
	if (!m_bIsMovementLocked && (Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATheMessengerCharacter::MoveRight(float Value)
{
	if ( !m_bIsMovementLocked && (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
