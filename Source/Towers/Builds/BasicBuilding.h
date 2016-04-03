// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemy/BasicEnemy.h"
#include "Effect/BasicEffect.h"
#include "BasicProjectile.h"
#include "BasicBuilding.generated.h"
USTRUCT(Blueprintable)
struct FTowerData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		/** Full Path of Blueprint */
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		FString Item_Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 range;
	/** Scriptable Use Code */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		UTexture2D * Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 projectileId;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		int32 type;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Properties")
		USkeletalMesh * Mesh;
};
class ABasicPlayerController;
UCLASS()
class TOWERS_API ABasicBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicBuilding();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void initTower(FTowerData building);
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		int32  id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		FString itemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		UTexture2D* icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	class USphereComponent *  BaseCollisionComponent;
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
		void Prox(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Item)	class UStaticMeshComponent * Mesh;	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)	class USkeletalMeshComponent * Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	bool isBuild = false;
	UDataTable * ProjectileObjects = nullptr;
	UDataTable * EffectObjects = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Build")
		int32 projectileId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	ABasicEnemy * targetEnemy = nullptr;
	UFUNCTION(BlueprintCallable, Category = "Build")
	void StartBuild(FTowerData building);
	ABasicPlayerController * PController = nullptr;
	virtual void Shoot();
	UFUNCTION()
	void OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void FindTarget();
	FEffectData effect;
	void GetEffectStruct();

	FProjectileData  projectile;
	void GetProjectileStruct();
};
