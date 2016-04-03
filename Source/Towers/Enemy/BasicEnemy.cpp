// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "BasicEnemy.h"
#include"EnemyAIController.h"
#include "BasicProjectile.h"
#include "Builds/StrategicPoint.h"


// Sets default values
ABasicEnemy::ABasicEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABasicEnemy::OnProjectileHit);
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (health > 0) {
		Moving();
	}
	else {
		Destroy();
	}
	
}

// Called to bind functionality to input
void ABasicEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ABasicEnemy::Moving() {
	
	if (targetPoint != nullptr) {
		 AEnemyAIController *ai = Cast<AEnemyAIController>(GetController());
		 if (ai != nullptr) {
			 ai->MoveToLocation(targetPoint->GetActorLocation());
		 }
	}
	else {
		MakePath();
	}
}

void ABasicEnemy::MakePath() {
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStrategicPoint::StaticClass(), FoundActors);
	for (auto it = FoundActors.CreateIterator(); it; ++it) {
		AStrategicPoint * target = Cast<AStrategicPoint>(*it);
		if (target != nullptr) {
			targetPoint = target;
			break;
		}
	}
}

void ABasicEnemy::OnProjectileHit(AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &
	SweepResult) {
	ABasicProjectile * projectile = Cast<ABasicProjectile>(OtherActor);
	if (projectile != nullptr) {
		if (projectile->isMoving) {
			if (health > 0) {
				health -= projectile->damage;
				if (health <= 0) {
					Destroy();
				}
			}
			else {
				Destroy();
			}
		}
	}
}
void ABasicEnemy::MakeDamage(float damage) {
	if (health > 0) {
		health -=damage;
	}
}