// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "BeamProjectile.h"
#include "Builds/BasicBuilding.h"
#include "Enemy/BasicEnemy.h"

ABeamProjectile::ABeamProjectile() {
	//GenerateProjectyle();

}
void ABeamProjectile::BeginPlay()
{
	Super::BeginPlay();
}
void ABeamProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (tower->targetEnemy != nullptr) {
		Particle->SetBeamTargetPoint(0, tower->targetEnemy->GetActorLocation(), 0);
	}

}
void ABeamProjectile::GenerateProjectyle() {
	
	/*Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->AttachTo(RootComponent);*/
	//Particle->SetBeamSourcePoint(1, FVector(0, 400, 70),1);
	//Particle->SetBeamTargetPoint(1, FVector(800, 300, 200),1);
	//Particle->SetActorParameter("BeamSource", source);
	//Particle->SetActorParameter("BeamTarget", enemy);
	//Particle->ActivateSystem();
	//Particle->DeactivateSystem();
}
void ABeamProjectile::InitProjectile(const FVector& Direction, FProjectileData projectile) {
	Particle->SetTemplate(projectile.EffectTemplate);
	Particle->SetBeamSourcePoint(1, GetActorLocation(), 1);
	Particle->SetBeamTargetPoint(0, tower->targetEnemy->GetActorLocation(), 0);
	lifeTime = projectile.lifeTime;
	FTimerHandle FuzeTimerHandle;
	if (lifeTime == 0) {
		lifeTime = 0.1f;
	}
	GetWorldTimerManager().SetTimer(FuzeTimerHandle, this, &ABeamProjectile::BeamDead, lifeTime, true);
	
}
void ABeamProjectile::BeamDead() {
	Destroy();
}