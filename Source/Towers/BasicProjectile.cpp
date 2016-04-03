// Fill out your copyright notice in the Description page of Project Settings.

#include "Towers.h"
#include "Enemy/BasicEnemy.h"
#include "Effect/BasicEffect.h"
#include "Builds/BasicBuilding.h"
#include "Main/BasicPlayerController.h"
#include "BasicProjectile.h"


// Sets default values
ABasicProjectile::ABasicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GenerateProjectyle();
	
}

// Called when the game starts or when spawned
void ABasicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

void ABasicProjectile::InitProjectile(const FVector& Direction, FProjectileData projectile)
{
	MovementComp->InitialSpeed = projectile.speed;
	MovementComp->MaxSpeed = projectile.speed;
	MovementComp->Velocity = MovementComp->InitialSpeed * Direction;
	
	MovementComp->ProjectileGravityScale = projectile.weight;
	CollisionComp->SetSphereRadius(projectile.CollisionRadius);
	if (projectile.Mesh) {
		MeshComp->SetStaticMesh(projectile.Mesh);
	}
	damage = projectile.Damage;
	SetActorLocation(FVector(tower->GetActorLocation().X, tower->GetActorLocation().Y, tower->GetActorLocation().Z + 200));
}

void ABasicProjectile::OnHit(FHitResult const& HitResult)
{
	//OnProjectileDestroyed();
	ABasicPlayerController * controller = Cast<ABasicPlayerController>(GetWorld()->GetFirstPlayerController());
	if (controller != nullptr) {
		ABasicEffect * effect = controller->effectFactory->MakeEffect(tower,GetWorld());
		if (effect != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Bang");
			effect->SetActorLocation(GetActorLocation());
		}
	}
	this->Destroy();

}
void ABasicProjectile::OnProjectileHit(AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &
	SweepResult) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, "HIT");
	if (isMoving) {
		
		ABasicEnemy * enemy = Cast<ABasicEnemy>(OtherActor);
		if (enemy != nullptr) {
			enemy->MakeDamage(damage);
		}
		this->Destroy();

	}
}
void ABasicProjectile::OnProjectileDestroyed_Implementation() {
	isMoving = false;
}
void ABasicProjectile::GenerateProjectyle() {
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(1.0f);
	CollisionComp->AlwaysLoadOnClient = true;
	CollisionComp->AlwaysLoadOnServer = true;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionComp->bCanEverAffectNavigation = false;
	RootComponent = CollisionComp;
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABasicProjectile::OnProjectileHit);
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->OnProjectileStop.AddDynamic(this, &ABasicProjectile::OnHit);
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->AttachTo(RootComponent);
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	Particle->AttachTo(RootComponent);
	
}