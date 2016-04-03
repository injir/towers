// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "BasicBuilds.h"


// Sets default values
ABasicBuilds::ABasicBuilds()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	BaseCollisionComponent->InitSphereRadius(302.0f);
	BaseCollisionComponent->bGenerateOverlapEvents = true;
	BaseCollisionComponent->AttachTo(RootComponent);
	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicBuilds::Prox);
	

}

// Called when the game starts or when spawned
void ABasicBuilds::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicBuilds::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABasicBuilds::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


void ABasicBuilds::Prox(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32
	OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	
}