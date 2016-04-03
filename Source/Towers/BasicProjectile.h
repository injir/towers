// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BasicProjectile.generated.h"

class ABasicBuilding;
USTRUCT(Blueprintable)
struct FProjectileData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		/** Full Path of Blueprint */
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 CollisionRadius;
	/** Scriptable Use Code */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		UTexture2D * Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 Damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		float speed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 weight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 EffectId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		UStaticMesh * Mesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		UParticleSystem * EffectTemplate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
	float lifeTime;

};

UCLASS(Blueprintable)
class TOWERS_API ABasicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	 ABasicProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	virtual void GenerateProjectyle();
	/** movement component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UProjectileMovementComponent* MovementComp;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UStaticMeshComponent * MeshComp;
	/** collisions */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComp;
	/** blueprint event: projectile hit something */
	UFUNCTION()
	void OnProjectileHit(AActor* OtherActor, UPrimitiveComponent*
		OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &
		SweepResult);

	/** blueprint event: projectile hit something */
	UFUNCTION(BlueprintNativeEvent, Category = "Projectile")
		void OnProjectileDestroyed();

	/** initial setup */
	UFUNCTION(BlueprintCallable, Category = Projectile)
	virtual void InitProjectile(const FVector& Direction, FProjectileData projectile);
	ABasicBuilding * tower = nullptr;
	/** handle hit */
	UFUNCTION()
		void OnHit(const FHitResult& HitResult);
	bool isMoving = true;
	float damage = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		UParticleSystemComponent * Particle;
};
