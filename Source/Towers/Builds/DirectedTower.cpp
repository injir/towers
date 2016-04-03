// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "Kismet/KismetMathLibrary.h"
#include "DirectedTower.h"


ADirectedTower::ADirectedTower() {

}

void ADirectedTower::Shoot() {
	Super::Shoot();
	
}
void ADirectedTower::initTower(FTowerData building) {
	Super::initTower(building);
}