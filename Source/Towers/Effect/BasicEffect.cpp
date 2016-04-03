// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "BasicEffect.h"
#include "Enemy/BasicEnemy.h"


// Sets default values
ABasicEffect::ABasicEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->SetSphereRadius(100);
	RootComponent = CollisionComp;
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->AttachTo(RootComponent);

}

// Called when the game starts or when spawned
void ABasicEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEffect::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	MakeEffect();
}

void ABasicEffect::DestroyEffect() {
	//Destroy();
}
void ABasicEffect::MakeEffect() {
	TArray<AActor *> insideActor;
	CollisionComp->GetOverlappingActors(insideActor,ABasicEnemy::StaticClass());
	for (auto It = insideActor.CreateIterator(); It; ++It) {
		ABasicEnemy * enemy = Cast<ABasicEnemy>(*It);
		enemy->MakeDamage(50);
	}
}