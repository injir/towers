// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BasicBuilds.generated.h"

UCLASS()
class TOWERS_API ABasicBuilds : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicBuilds();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Basic)
		USphereComponent *  BaseCollisionComponent = nullptr;
	UFUNCTION()
		void Prox(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32
			OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//ABasicEnemy * targetEnemy = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)	class USkeletalMeshComponent *  MeshComponent = nullptr;
};
