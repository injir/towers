// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Builds/BasicBuilding.h"
#include "BeamTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERS_API ABeamTower : public ABasicBuilding
{
	GENERATED_BODY()
public:
	virtual void Shoot() override;
	
	
	
};
