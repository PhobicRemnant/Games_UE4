// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "ToonTanks/HealthComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));


}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Rotate firing turret to aim
void APawnBase::RotateTurret(FVector LookAtTarget)
{
	// 
	FVector StartLocation = TurretMesh->GetComponentLocation();
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation,	FVector(LookAtTarget.X, LookAtTarget.Y,	TurretMesh->GetComponentLocation().Z ) );
	// Rotate Turret
	TurretMesh->SetWorldRotation(TurretRotation);
}
// Fire cannon
void APawnBase::Fire()
{
	// Fire proyectile from cannon

	if(ProjectileClass)
	{
		// Location and rotation for the bullet
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProyectileBase* TempProjectile = GetWorld()->SpawnActor<AProyectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	
	}
}
// Destruction
void APawnBase::HandleDestruction()
{
	// Death effects particle
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());

	// Death sound effect
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	// Shake camera effect on death
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);

}	