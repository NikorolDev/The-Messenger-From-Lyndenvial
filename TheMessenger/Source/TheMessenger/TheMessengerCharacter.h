// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TheMessengerCharacter.generated.h"

class APlayerController;

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
	AActor* FocusedActor;

	ADialogueManager* m_pcDialogueManager;

	APlayerController* m_pcPlayerController;

	UPlayerHUD* m_pcPlayerHUD;

	UPROPERTY( Category = "Properties|Line Trace", EditInstanceOnly, meta = ( DisplayName = "Line Trace Distance" ) )
		float m_fLineTraceDistance;

	void TraceForward();

	void OnInteractPressed();

	UFUNCTION()
		void SetPlayerBackFromSequence();

public:
	ATheMessengerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	void SetPlayerForSequence( const FVector& v3PlayerPosition, float PlayerRotationYaw );

	UFUNCTION( BlueprintCallable)
		UPlayerHUD* GetPlayerHUD();

	APlayerController& GetPlayerController() const;

protected:

	UPROPERTY( Category = "Properties|HUD", EditInstanceOnly, BlueprintReadOnly, meta = ( DisplayName = "Player HUD" ) )
		TSubclassOf<UPlayerHUD> m_tcPlayerHUD;


	/** Resets HMD orientation in VR. */
	void OnResetVR();

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

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

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

