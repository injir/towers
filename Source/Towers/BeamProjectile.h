// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicProjectile.h"

#include "BeamProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TOWERS_API ABeamProjectile : public ABasicProjectile
{
	GENERATED_BODY()
public:
	ABeamProjectile();
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;
		virtual void GenerateProjectyle() override;
		virtual void InitProjectile(const FVector& Direction, FProjectileData projectile) override;
		//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		//UParticleSystemComponent * Particle;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		AActor* enemy = nullptr;
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		AActor* source = nullptr;
		UFUNCTION()
		void BeamDead();
		float lifeTime;
};
