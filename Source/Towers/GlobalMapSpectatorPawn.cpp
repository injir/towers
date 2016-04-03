// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "GlobalMapSpectatorPawn.h"
#include "Main/BasicPlayerController.h"
#include "Main/BasicSpectatorPawnMovement.h"

AGlobalMapSpectatorPawn::AGlobalMapSpectatorPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	// Disable Jump and Crouch actions
	bAddDefaultMovementBindings = false;
	// Configure character movement
	/*GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;*/
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = false; // Rotate arm relative to character
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level									  // Move camera boom with character only on yaw rotation
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = true;

	// Enables camera lag - matter of taste
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;

	// Disable collisions
	GetCollisionComponent()->bGenerateOverlapEvents = false;
	GetCollisionComponent()->SetCollisionProfileName("NoCollision");

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}
void AGlobalMapSpectatorPawn::ChangeCameraArmLength(float changeValue)
{
	CameraBoom->TargetArmLength += changeValue * 100.0f; // Change 100.0f with zoom speed property
}

void AGlobalMapSpectatorPawn::RotateCameraArm(FRotator rotation)
{
	CameraBoom->AddRelativeRotation(rotation);
}

void AGlobalMapSpectatorPawn::MoveCharacterForward(float changeValue)
{
	AddMovementInput(GetActorForwardVector(), changeValue);
}

void AGlobalMapSpectatorPawn::MoveCharacterRight(float changeValue)
{
	AddMovementInput(GetActorRightVector(), changeValue);
}





