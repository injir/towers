// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "Main/BasicPlayerController.h"
#include "BeamTower.h"


void ABeamTower::Shoot() {
	
	FHitResult RV_Hit;
	if (targetEnemy != nullptr) {
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
		RV_TraceParams.bTraceComplex = true;
		RV_TraceParams.bTraceAsyncScene = true;
		RV_TraceParams.bReturnPhysicalMaterial = false;
		GetWorld()->LineTraceSingle(
			RV_Hit,        //result
			FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z + 200),    //start
			targetEnemy->GetActorLocation(), //end
			ECC_Pawn, //collision channel
			RV_TraceParams
			);
		ABasicEnemy * enemy = Cast<ABasicEnemy>(RV_Hit.GetActor());

		ABasicProjectile * Pro = PController->projectileFactory->SpawnProjectile(projectile.type, GetWorld());
		if (Pro != nullptr) {			
			Pro->tower = this;
			Pro->SetActorLocation(GetActorLocation());
			Pro->SetActorRotation(GetActorRotation());
			FVector ShootDirection = GetActorRotation().Vector();
			ShootDirection.Normalize();
			Pro->InitProjectile(ShootDirection, projectile);
			if (enemy != nullptr) {
				enemy->MakeDamage(Pro->damage);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, enemy->GetName());
			}
		}
	}
}

