// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "Enemy/BasicEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Main/BasicPlayerController.h"
#include "BasicBuilding.h"


// Sets default values
ABasicBuilding::ABasicBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseCollisionComponent"));
	RootComponent = Mesh;
	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	BaseCollisionComponent->InitSphereRadius(302.0f);
	BaseCollisionComponent->AttachTo(RootComponent);
	//BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicBuilding::Prox);
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemBodyComponent"));
	Body->AttachTo(BaseCollisionComponent);
	Body->RelativeRotation = FRotator(0, -90, 0);
	static ConstructorHelpers::FObjectFinder<UDataTable> itemsData(TEXT("DataTable'/Game/Data/ProjectileData.ProjectileData'"));
	ProjectileObjects = itemsData.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> effectData(TEXT("DataTable'/Game/Data/EffectData.EffectData'"));
	EffectObjects = effectData.Object;
	 //PController = GetWorld()->GetFirstPlayerController();
}

// Called when the game starts or when spawned
void ABasicBuilding::BeginPlay()
{
	Super::BeginPlay();
	PController = Cast<ABasicPlayerController>(GetWorld()->GetFirstPlayerController());
	FTimerHandle FuzeTimerHandle;
	GetWorldTimerManager().SetTimer(FuzeTimerHandle,this, &ABasicBuilding::Shoot, 1.0f, true);
}

// Called every frame
void ABasicBuilding::Tick( float DeltaTime )
{

	Super::Tick( DeltaTime );
	if (targetEnemy == nullptr) {
		FindTarget();
	}
	else {		
		FVector Direction = FVector((targetEnemy->GetActorLocation().X- GetActorLocation().X ), (targetEnemy->GetActorLocation().Y- GetActorLocation().Y), 0);
		Direction.Normalize();
		FRotator rotate = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), targetEnemy->GetActorLocation());
		SetActorRotation(rotate);
	}
}

void ABasicBuilding::StartBuild(FTowerData building) {

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta,"Build");
	if (!isBuild) {
		Body->SetSkeletalMesh(building.Mesh);
		projectileId = building.projectileId;
		isBuild = true;
		BaseCollisionComponent->SetSphereRadius(building.range);
		BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicBuilding::Prox);
		BaseCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ABasicBuilding::OnEndOverlap);
		BaseCollisionComponent->OnComponentHit.AddDynamic(this, &ABasicBuilding::OnHit);
		
	}
}

void ABasicBuilding::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &
	SweepResult)
{
	if (targetEnemy == nullptr) {
		ABasicEnemy * enemy = Cast<ABasicEnemy>(OtherActor);
		if (enemy != nullptr)
		{
			targetEnemy = enemy;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, enemy->GetName());
		}

	}
}

void ABasicBuilding::OnEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ABasicEnemy * enemy = Cast<ABasicEnemy>(OtherActor);
	if (enemy != nullptr && targetEnemy != nullptr)
	{
		if (enemy->GetName() == targetEnemy->GetName()) {
			targetEnemy = nullptr;
			
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "target clear");
		}
	}
}

void ABasicBuilding::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "target hit");
	
}

void ABasicBuilding::FindTarget() {
	TArray<AActor*>findActors;
	BaseCollisionComponent->GetOverlappingActors(findActors, ABasicEnemy::StaticClass());
	for (auto It = findActors.CreateIterator(); It; ++It) {
		
		ABasicEnemy * enemy = Cast<ABasicEnemy>(*It);
		if (enemy != nullptr) {
			targetEnemy = enemy;
			break;
		}
	}
}

void ABasicBuilding::initTower(FTowerData building) {
	Body->SetSkeletalMesh(building.Mesh);
	projectileId = building.projectileId;
	isBuild = true;
	BaseCollisionComponent->SetSphereRadius(building.range);
	BaseCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasicBuilding::Prox);
	BaseCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ABasicBuilding::OnEndOverlap);
	BaseCollisionComponent->OnComponentHit.AddDynamic(this, &ABasicBuilding::OnHit);
	GetProjectileStruct();
	GetEffectStruct();
}

void ABasicBuilding::Shoot(){
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::FromInt(projectileId));
	if (targetEnemy != nullptr) {
		ABasicProjectile * Pro = PController->projectileFactory->SpawnProjectile(projectile.type, GetWorld());
		if (Pro != nullptr) {
			//Pro->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 200));
			Pro->tower = this;
			Pro->SetActorLocation(GetActorLocation());
			Pro->SetActorRotation(GetActorRotation());
			FVector ShootDirection = GetActorRotation().Vector();
			ShootDirection.Normalize();
			Pro->InitProjectile(ShootDirection, projectile);

		}
	}
}



void ABasicBuilding::GetProjectileStruct(){
	static const FString ContextString(TEXT("GENERAL"));
	FProjectileData * item = ProjectileObjects->FindRow<FProjectileData>(*FString::Printf(
		TEXT("%d"),
		projectileId), ContextString);
	if (item != nullptr) {
		projectile = *item;
	}
}

void ABasicBuilding::GetEffectStruct() {
	static const FString ContextString(TEXT("GENERAL"));
	FEffectData * item = EffectObjects->FindRow<FEffectData>(*FString::Printf(
		TEXT("%d"),
		projectile.EffectId), ContextString);
	if (item != nullptr) {
		effect = *item;
	}
	
}