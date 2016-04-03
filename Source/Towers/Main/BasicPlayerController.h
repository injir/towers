// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Builds/BasicBuilding.h"
#include "TowerFactory.h"
#include "Effect/EffectFactory.h"
#include "Builds/BasicFoundation.h"
#include "ProjectileFactory.h"
#include "BasicPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERS_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasicPlayerController(const FObjectInitializer& ObjectInitializer);
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	FTowerData ChoosenTower;*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic")
	ABasicBuilding * clickedBuilding;
	UFUNCTION(BlueprintCallable, Category = "Basic")
	void TowerBuild();
	UFUNCTION(BlueprintCallable, Category = "Basic")
	void ChooseTargetUnderMouseCursor();
	UTowerFactory * towerFactory;
	UEffectFactory * effectFactory;
	UProjectileFactory * projectileFactory;
	ABasicFoundation * foundation = nullptr;
	UFUNCTION(BlueprintCallable, Category = "Basic")
		void Build(FString name);
protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// Методы управления камерой спектатора
	void OnMoveForwardAxis(float axisValue);
	void OnMoveRightAxis(float axisValue);
	void OnMouseHorizontal(float axisValue);
	void OnMouseVertical(float axisValue);
	void OnZoomInAction();
	void OnZoomOutAction();
	void OnLookAroundStart();
	void OnLookAroundStop();
	
	//---------------------------------
private:
	bool lookAroundEnabled = false;
	int32 mouseLockPositionX;
	int32 mouseLockPositionY;

};
