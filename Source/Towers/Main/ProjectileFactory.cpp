// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "BasicProjectile.h"
#include "BeamProjectile.h"
#include "ProjectileFactory.h"

UProjectileFactory::UProjectileFactory() {

}

ABasicProjectile *  UProjectileFactory::SpawnProjectile(int32 type, UWorld * world) {
	ABasicProjectile * projectile = nullptr;
	switch (type)
	{
	case 0: {
		ABasicProjectile * obj = world->SpawnActor<ABasicProjectile>(ABasicProjectile::StaticClass());
		if (obj != nullptr) {
			return obj;
		}
	};
	case 1: {
		ABeamProjectile * obj = world->SpawnActor<ABeamProjectile>(ABeamProjectile::StaticClass());
		if (obj != nullptr) {
			return obj;
		}
	};
	default:
		return projectile;
	}
}
