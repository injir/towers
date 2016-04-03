// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "StrategicPoint.h"


// Sets default values
AStrategicPoint::AStrategicPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStrategicPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStrategicPoint::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

