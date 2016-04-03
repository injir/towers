// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BasicEffect.generated.h"
USTRUCT(Blueprintable)
struct FEffectData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		/** Full Path of Blueprint */
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		UParticleSystem * EffectTemplate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		float damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		float damagePerSecond;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 BuffType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		float Duration;


};

UCLASS()
class TOWERS_API ABasicEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicEffect();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	UParticleSystemComponent * Particle;
	USphereComponent * CollisionComp;
	virtual void MakeEffect();
	virtual void DestroyEffect();
	
};
