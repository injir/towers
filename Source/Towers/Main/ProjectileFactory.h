// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ActorFactories/ActorFactory.h"
#include "BasicProjectile.h"
#include "ProjectileFactory.generated.h"

/**
 * 
 */
UCLASS()
class TOWERS_API UProjectileFactory : public UActorFactory
{
	GENERATED_BODY()
	
public:
	UProjectileFactory();
	ABasicProjectile * SpawnProjectile(int32 type, UWorld * world);
	
	
};
