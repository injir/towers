// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BasicFoundation.generated.h"

UCLASS()
class TOWERS_API ABasicFoundation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicFoundation();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)	class UStaticMeshComponent * Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		bool isBuild = false;
};
