// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "BasicFoundation.h"


// Sets default values
ABasicFoundation::ABasicFoundation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseCollisionComponent"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ABasicFoundation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicFoundation::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

