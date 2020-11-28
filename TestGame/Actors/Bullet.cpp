// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Proyectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	RootComponent = ProjectileMesh;

	// Proyectile properties
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Proyectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->ProjectileGravityScale = 0.03;


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	// Play launch sound when you fire the weapon
	// Muzzle flash
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();

	// Avoid nullprt crash in case there is no Owner
	if (!MyOwner)
	{
		return;
	}
	// If the other actor isn't self  OR owner AND exist then apply damage
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(),
			this, DamageType);

		// Play effects
		// Shoot sound
		// Muzzle flash

	}

	// Destroy the object to avoid flying bullets after collision
	//Destroy();

}