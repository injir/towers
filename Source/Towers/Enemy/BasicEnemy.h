// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Builds/StrategicPoint.h"
#include "BasicEnemy.generated.h"

UCLASS()
class TOWERS_API ABasicEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		float  health = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	AStrategicPoint * targetPoint = nullptr;
	void Moving();
	void MakePath();
	UFUNCTION()
	void OnProjectileHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	void MakeDamage(float damage);
};
