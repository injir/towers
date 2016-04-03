// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActorFactories/ActorFactory.h"
#include "Builds/BasicBuilding.h"
#include "TowerFactory.generated.h"

/**
 * 
 */
UCLASS()
class TOWERS_API UTowerFactory : public UActorFactory
{
	GENERATED_BODY()
public:
	UTowerFactory();
	ABasicBuilding * BuildTower(FString name, UWorld * const world);
	UDataTable * TowerObjects;
	FTowerData getTowerTableRow(FString name);
};
