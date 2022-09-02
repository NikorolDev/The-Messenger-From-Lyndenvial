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

void ATheMessengerCharacter::TraceForward()
{
	FHitResult OutHit;
	FVector v3StartPosition = FollowCamera->GetComponentLocation();
	FVector v3Forward = FollowCamera->GetForwardVector();
	FVector v3EndPosition = v3StartPosition + ( v3Forward * m_fLineTraceDistance );

	FCollisionQueryParams CollisionParams;
	//CollisionParams.AddIgnoredActor( this->GetOwner() );

	bool bHit = GetWorld()->LineTraceSingleByChannel( OutHit, v3StartPosition, v3EndPosition, ECC_Visibility, CollisionParams );
	//DrawDebugLine( GetWorld(), v3StartPosition, v3EndPosition, FColor::Green, false, 1.0f );

	if( bHit )
	{
		//DrawDebugBox( GetWorld(), OutHit.ImpactPoint, FVector( 5, 5, 5 ), FColor::Red, false, 1.0f );

		AActor* Interactable = OutHit.GetActor();

		if( Interactable )
		{
			if( Interactable != FocusedActor )
			{
				if( FocusedActor )
				{
					IInteractableInterface* Interface = Cast<IInteractableInterface>( FocusedActor );
					if( Interface )
					{
						Interface->LostFocus_Implementation();
					}
				}
				IInteractableInterface* Interface = Cast<IInteractableInterface>( Interactable );
				if( Interface )
				{
					Interface->OnFocus_Implementation();
				}
				FocusedActor = Interactable;
			}
		}
		else
		{
			if( FocusedActor )
			{
				IInteractableInterface* Interface = Cast<IInteractableInterface>( FocusedActor );
				if( Interface )
				{
					Interface->LostFocus_Implementation();
				}
			}
			FocusedActor = nullptr;
		}
	}
	else
	{
		if( FocusedActor )
		{
			IInteractableInterface* Interface = Cast<IInteractableInterface>( FocusedActor );
			if( Interface )
			{
				Interface->LostFocus_Implementation();
			}
		}
		FocusedActor = nullptr;
	}
}

void ATheMessengerCharacter::OnInteractPressed()
{
	if( FocusedActor )
	{
		IInteractableInterface* Interface = Cast<IInteractableInterface>( FocusedActor );
		if( Interface )
		{
			Interface->OnInteract_Implementation( FocusedActor );
		}
	}
}

void ATheMessengerCharacter::SetPlayerBackFromSequence()
{
	if( !m_bInEndDaySequence )
	{
		m_pcPlayerController->SetInputMode( FInputModeGameOnly() );
		//EnableInput( m_pcPlayerController );
	}

	m_bIsMovementLocked = false;
}

ATheMessengerCharacter::ATheMessengerCharacter()
	:m_fLineTraceDistance (2000.0f)
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction( "Interact", IE_Pressed, this, &ATheMessengerCharacter::OnInteractPressed );

	PlayerInputComponent->BindAxis("MoveForward", this, &ATheMessengerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATheMessengerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATheMessengerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATheMessengerCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATheMessengerCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATheMessengerCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATheMessengerCharacter::OnResetVR);
}

void ATheMessengerCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_v3SpawnLocation = GetActorLocation();

	m_pcDialogueManager = Cast<ADialogueManager>( UGameplayStatics::GetActorOfClass( GetWorld(), ADialogueManager::StaticClass() ) );
	m_pcPlayerController = Cast<APlayerController>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ) );

	// Create the player widget and add it to the viewport.
	m_pcPlayerHUD = CreateWidget<UPlayerHUD>( m_pcPlayerController, m_tcPlayerHUD );
	m_pcPlayerHUD->AddToViewport(-1);

	//m_pcDialogueManager->DialogueFinished.BindUObject( this, &ATheMessengerCharacter::SetPlayerBackFromSequence );
	//m_pcDialogueManager->DialogueFinished.AddDynamic( this, &ATheMessengerCharacter::SetPlayerBackFromSequence );
	m_pcDialogueManager->DialogueFinished.AddUObject( this, &ATheMessengerCharacter::SetPlayerBackFromSequence );
}


void ATheMessengerCharacter::Tick( float DeltaTime )
{
	TraceForward();
}

void ATheMessengerCharacter::SetPlayerForSequence( const FVector& v3PlayerPosition, float PlayerRotationYaw )
{
	m_bIsMovementLocked = true;
	//DisableInput( m_pcPlayerController );
	m_pcPlayerController->SetInputMode( FInputModeUIOnly() );
	SetActorLocation( v3PlayerPosition );
	m_pcPlayerController->SetControlRotation( FRotator( 0, PlayerRotationYaw, 0 ) );
}

void ATheMessengerCharacter::SetInEndDaySequence( bool bInEndDaySequence )
{
	m_bInEndDaySequence = bInEndDaySequence;
}

void ATheMessengerCharacter::SetLocationToSpawn()
{
	//SetActorLocation( m_v3SpawnLocation );
	SetActorLocation( FVector( 362, -20482, 650 ) );
	m_pcPlayerController->SetInputMode( FInputModeGameOnly() );
}

UPlayerHUD* ATheMessengerCharacter::GetPlayerHUD()
{
	return m_pcPlayerHUD;
}

APlayerController& ATheMessengerCharacter::GetPlayerController() const
{
	return *m_pcPlayerController;
}

void ATheMessengerCharacter::OnResetVR()
{
	// If TheMessenger is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in TheMessenger.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATheMessengerCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ATheMessengerCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ATheMessengerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATheMessengerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
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
