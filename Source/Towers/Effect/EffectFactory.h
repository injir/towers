// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActorFactories/ActorFactory.h"
#include "Effect/BasicEffect.h"
#include "Builds/BasicBuilding.h"
#include "EffectFactory.generated.h"

/**
 * 
 */
UCLASS()
class TOWERS_API UEffectFactory : public UActorFactory
{
	GENERATED_BODY()
public:
	UEffectFactory();
		ABasicEffect * MakeEffect(ABasicBuilding * tower, UWorld * const world);
	
	
	
};
