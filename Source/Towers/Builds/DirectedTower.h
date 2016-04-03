// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Builds/BasicBuilding.h"
#include "DirectedTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERS_API ADirectedTower : public ABasicBuilding
{
	GENERATED_BODY()
public:	
	ADirectedTower();
	virtual void Shoot() override;
	virtual void initTower(FTowerData building) override;
};
