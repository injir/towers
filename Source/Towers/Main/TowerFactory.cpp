// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "Builds/BasicBuilding.h"
#include "Builds/AOETower.h"
#include "Builds/BuffTower.h"
#include "Builds/SelfDirectedTower.h"
#include "Builds/BeamTower.h"
#include "Builds/DirectedTower.h"
#include "TowerFactory.h"

UTowerFactory::UTowerFactory() {
	static ConstructorHelpers::FObjectFinder<UDataTable> itemsData(TEXT("DataTable'/Game/Data/BuildingData.BuildingData'"));
	TowerObjects = itemsData.Object;
}

ABasicBuilding * UTowerFactory::BuildTower(FString name, UWorld * const world) {
	FTowerData building = getTowerTableRow(name);
	ABasicBuilding * tower = nullptr;
	/*tower = world->SpawnActor<ABasicBuilding>(ABasicBuilding::StaticClass());
	if (tower != nullptr) {
		tower->initTower(building);
	}
	return tower;*/
		switch (building.type)
		{
		case 1: {
			ADirectedTower * directTower = world->SpawnActor<ADirectedTower>(ADirectedTower::StaticClass());
			if (directTower != nullptr) {
				directTower->initTower(building);
				return directTower;
			}
		};
		case 2: {
			AAOETower * AOETower = world->SpawnActor<AAOETower>(AAOETower::StaticClass());
			if (AOETower != nullptr) {
				AOETower->initTower(building);
				return  AOETower;
			}
		};
		case 3: {
			ASelfDirectedTower * SelfTower = world->SpawnActor<ASelfDirectedTower>(ASelfDirectedTower::StaticClass());
			if (SelfTower != nullptr) {
				SelfTower->initTower(building);
				return  SelfTower;
			}
		}
		case 4: {
			ABeamTower * obj = world->SpawnActor<ABeamTower>(ABeamTower::StaticClass());
			if (obj != nullptr) {
				obj->initTower(building);
				return  obj;
			}
		}
		default:
			return tower;
		}
	
}
FTowerData UTowerFactory::getTowerTableRow(FString name) {
	FTowerData * tower;
	static const FString ContextString(TEXT("GENERAL"));
	tower = TowerObjects->FindRow<FTowerData>(*name, ContextString);
	if (tower != nullptr) {
		return *tower;
	}
	return FTowerData();
}