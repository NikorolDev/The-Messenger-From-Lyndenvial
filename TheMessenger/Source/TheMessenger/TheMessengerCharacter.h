// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TheMessengerCharacter.generated.h"

// Forward class declarations (Engine)
class APlayerController;

// Forward class declarations (Game)
class ADialogueManager;
class UPlayerHUD;

UCLASS(config=Game)
class ATheMessengerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

private:
	// Whether the movement is locaked which stops from moving anywhere.
	bool m_bIsMovementLocked;

	// If the player is on the end day sequence.
	bool m_bInEndDaySequence;

	// The rotation the player spawned in.
	FRotator m_v3SpawnRotation;

	// The location the player spawnedin.
	FVector m_v3SpawnLocation;

	// The focused actor that is interactable.
	AActor* m_pcFocusedActor;

	// The dilaogue manager to bind it when the player is out of dialogue sequence.
	ADialogueManager* m_pcDialogueManager;

	// The player controller to disable input and enable it in certain situations.
	APlayerController* m_pcPlayerController;

	// The player HUD that is created here and is referenced in the hint manager.
	UPlayerHUD* m_pcPlayerHUD;

	// The Line trace distance to check for interactables.
	UPROPERTY( Category = "Properties|Line Trace", EditInstanceOnly, meta = ( DisplayName = "Line Trace Distance" ) )
		float m_fLineTraceDistance;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: TraceForward()
	// Author			: Nikodem Hamrol
	// Purpose			: To line trace on every tick to detected any interactables.
	//----------------------------------------------------------------------------------------------------------------------------
	void TraceForward();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: OnInteractPressed()
	// Author			: Nikodem Hamrol
	// Purpose			: Input bound function to interact with interactables.
	//----------------------------------------------------------------------------------------------------------------------------
	void OnInteractPressed();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetPlayerBackFromSequence()
	// Author			: Nikodem Hamrol
	// Purpose			: On dialogue finished it will set the player to move again and enable input.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION()
		void SetPlayerBackFromSequence();

public:
	//----------------------------------------------------------------------------------------------------------------------------
	// Constructor Name	: ADialogueManager()
	// Author			: Nikodem Hamrol
	// Notes			: Sets up the components and default values.
	//----------------------------------------------------------------------------------------------------------------------------
	ATheMessengerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetPlayerForSequence( const FVector& v3PlayerPosition, float PlayerRotationYaw )
	// Author			: Nikodem Hamrol
	// Purpose			: Set the player for sequence, which will set the location and rotation calculated by the villager and
	//					,	disabling movement.
	// Parameters		: v3PlayerPosition - New player position for sequence.
	//					, PlayerRotationYaw - The yaw rotation set to face the villager.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetPlayerForSequence( const FVector& v3PlayerPosition, float PlayerRotationYaw );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetInEndDaySequence( bool bInEndDaySequence )
	// Author			: Nikodem Hamrol
	// Purpose			: Set the player for sequence, which will set the location and rotation calculated by the villager and
	//					,	disabling movement.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetInEndDaySequence( bool bInEndDaySequence );

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: SetLocationToSpawn()
	// Author			: Nikodem Hamrol
	// Purpose			: Sets the player to be back spawn, which called on new day set.
	//----------------------------------------------------------------------------------------------------------------------------
	void SetLocationToSpawn();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetPlayerHUD()
	// Author			: Nikodem Hamrol
	// Purpose			: The player hud, which is used for hint manager.
	// Returns			: The player's HUD widget.
	//----------------------------------------------------------------------------------------------------------------------------
	UFUNCTION( BlueprintCallable)
		UPlayerHUD* GetPlayerHUD();

	//----------------------------------------------------------------------------------------------------------------------------
	// Function Name	: GetPlayerController()
	// Author			: Nikodem Hamrol
	// Purpose			: The player's controller to set input modes and disabling it.
	// Returns			: The player's Controller.
	//----------------------------------------------------------------------------------------------------------------------------
	APlayerController& GetPlayerController() const;

protected:
	// This is a sub class of the desired widget to be used as PLayer HUD.
	UPROPERTY( Category = "Properties|HUD", EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Player HUD" ) )
		TSubclassOf<UPlayerHUD> m_tcPlayerHUD;



	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

