// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "BasicPlayerController.h"
#include "Builds/BasicFoundation.h"
#include "GlobalMapSpectatorPawn.h"
#include "TowerFactory.h"
#include "ProjectileFactory.h"
#include "Effect/EffectFactory.h"


ABasicPlayerController::ABasicPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	towerFactory = NewObject<UTowerFactory>(UTowerFactory::StaticClass());
	effectFactory = NewObject<UEffectFactory>(UEffectFactory::StaticClass());
	projectileFactory = NewObject<UProjectileFactory>(UProjectileFactory::StaticClass());
}
void ABasicPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

//Ќазначает методы-обработчики дл€ ранее заданных кнопок управлени€ 
void ABasicPlayerController::SetupInputComponent()
{

	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ABasicPlayerController::OnMoveForwardAxis);
	InputComponent->BindAxis("MoveRight", this, &ABasicPlayerController::OnMoveRightAxis);
	InputComponent->BindAxis("MouseHorizontal", this, &ABasicPlayerController::OnMouseHorizontal);
	InputComponent->BindAxis("MouseVertical", this, &ABasicPlayerController::OnMouseVertical);
	InputComponent->BindAction("ZoomIn", EInputEvent::IE_Pressed, this, &ABasicPlayerController::OnZoomInAction);
	InputComponent->BindAction("ZoomOut", EInputEvent::IE_Pressed, this, &ABasicPlayerController::OnZoomOutAction);
	InputComponent->BindAction("Look", EInputEvent::IE_Pressed, this, &ABasicPlayerController::OnLookAroundStart);
	InputComponent->BindAction("Look", EInputEvent::IE_Released, this, &ABasicPlayerController::OnLookAroundStop);
	InputComponent->BindAction("Click", EInputEvent::IE_Pressed, this, &ABasicPlayerController::ChooseTargetUnderMouseCursor);
}


void ABasicPlayerController::OnMoveForwardAxis(float axisValue)
{

	APawn* const Pawn = GetPawn();
	AGlobalMapSpectatorPawn* character = Cast<AGlobalMapSpectatorPawn>(Pawn);
	if (character)
	{
		character->MoveCharacterForward(axisValue);
	}
}

void ABasicPlayerController::OnMoveRightAxis(float axisValue)
{
	APawn* const Pawn = GetPawn();
	AGlobalMapSpectatorPawn* character = Cast<AGlobalMapSpectatorPawn>(Pawn);
	if (character)
	{
		character->MoveCharacterRight(axisValue);
	}
}
// ≈сли зажата колесо мыши  осуществл€ем повороты камеры
void ABasicPlayerController::OnMouseHorizontal(float axisValue)
{
	if (lookAroundEnabled)
	{


		APawn* const Pawn = GetPawn();
		Pawn->AddControllerYawInput(axisValue);
		Cast<ULocalPlayer>(Player)->ViewportClient->Viewport->SetMouse(mouseLockPositionX, mouseLockPositionY);
	}
}

void ABasicPlayerController::OnMouseVertical(float axisValue)
{
	if (lookAroundEnabled)
	{


		APawn* const Pawn = GetPawn();
		AGlobalMapSpectatorPawn* character = Cast<AGlobalMapSpectatorPawn>(Pawn);
		if (character)
		{
			character->RotateCameraArm(FRotator(axisValue, 0.0f, 0.0f));
		}
		Cast<ULocalPlayer>(Player)->ViewportClient->Viewport->SetMouse(mouseLockPositionX, mouseLockPositionY);
	}
}

void ABasicPlayerController::OnZoomInAction()
{
	APawn* const Pawn = GetPawn();
	AGlobalMapSpectatorPawn* character = Cast<AGlobalMapSpectatorPawn>(Pawn);
	if (character)
	{
		character->ChangeCameraArmLength(-1.0f);
	}
}

void ABasicPlayerController::OnZoomOutAction()
{
	APawn* const Pawn = GetPawn();
	AGlobalMapSpectatorPawn* character = Cast<AGlobalMapSpectatorPawn>(Pawn);
	if (character)
	{
		character->ChangeCameraArmLength(1.0f);
	}
}

void ABasicPlayerController::OnLookAroundStart()
{
	lookAroundEnabled = true;
	bShowMouseCursor = false;
	mouseLockPositionX = Cast<ULocalPlayer>(Player)->ViewportClient->Viewport->GetMouseX();
	mouseLockPositionY = Cast<ULocalPlayer>(Player)->ViewportClient->Viewport->GetMouseY();
}

void ABasicPlayerController::OnLookAroundStop()
{

	lookAroundEnabled = false;
	bShowMouseCursor = true;
}

void ABasicPlayerController::TowerBuild() {
		
		/*if (ChoosenTower.Mesh) {
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, false, Hit);
			if (Hit.bBlockingHit)
			{
				FVector const& Location = FVector(Hit.ImpactPoint.X, Hit.ImpactPoint.Y, Hit.ImpactPoint.Z);
				FRotator const& Rotation = FRotator(Hit.ImpactPoint.X, Hit.ImpactPoint.Y, Hit.ImpactPoint.Z);
				ABasicBuilds* const NewBuilding = GetWorld()->SpawnActorDeferred<ABasicBuilds>(ABasicBuilds::StaticClass(), FTransform(), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
				if (NewBuilding != nullptr) {
					NewBuilding->GetMesh()->SetSkeletalMesh(ChoosenTower.Mesh);

					NewBuilding->SetActorLocation(Hit.ImpactPoint);
					FVector Orgin;
					FVector BoundsExtent;
					NewBuilding->GetActorBounds(false, Orgin, BoundsExtent);
					FString CoordinateString = FString::Printf(TEXT("Character Position is %s"), *BoundsExtent.ToCompactString());
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, CoordinateString);
				}
			}
		}*/
}

void ABasicPlayerController::ChooseTargetUnderMouseCursor() {
	foundation = nullptr;
	clickedBuilding = nullptr;
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Pawn, false, Hit);
	if (Hit.bBlockingHit) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, Hit.GetActor()->GetName());
			ABasicFoundation * found = Cast<ABasicFoundation>(Hit.GetActor());
			if (found != nullptr) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, found->GetName());
				foundation = found;
			}
		}

}
void ABasicPlayerController::Build(FString name) {
	if (foundation != nullptr) {
		FVector location = foundation->GetActorLocation();
		FRotator rotation = foundation->GetActorRotation();
		if (towerFactory != nullptr) {
		ABasicBuilding * tower = towerFactory->BuildTower(name, GetWorld());
		if (tower != nullptr) {
			
			tower->SetActorRotation(rotation);
			tower->SetActorLocation(location);
			foundation->Destroy();
			foundation = nullptr;
		}
		}
	}
}