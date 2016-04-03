// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "Effect/BasicEffect.h"
#include "EffectFactory.h"


UEffectFactory::UEffectFactory() {

}

ABasicEffect * UEffectFactory::MakeEffect(ABasicBuilding * tower, UWorld * const world) {
	ABasicEffect * effect = nullptr;
	if (tower != nullptr && world != nullptr) {
		effect = world->SpawnActor<ABasicEffect>(ABasicEffect::StaticClass());
		effect->Particle->SetTemplate(tower->effect.EffectTemplate);
	}
	return  effect;
}