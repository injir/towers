// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "Main/BasicPlayerController.h"
#include "GlobalMapSpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOWERS_API AGlobalMapSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
public:

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
public:
	AGlobalMapSpectatorPawn(const FObjectInitializer& ObjectInitializer);

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void ChangeCameraArmLength(float changeValue);
	void RotateCameraArm(FRotator rotation);
	void MoveCharacterForward(float changeValue);
	void MoveCharacterRight(float changeValue);


	
};
