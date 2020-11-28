// Fill out your copyright notice in the Description page of Project Settings.

#include "ProyectileBase.h"
#include "Camera/CameraShake.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
AProyectileBase::AProyectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProyectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Proyectile Mesh"));
	ProyectileMesh->OnComponentHit.AddDynamic(this, &AProyectileBase::OnHit);
	RootComponent = ProyectileMesh;

	// Proyectile properties
	ProyectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Proyectile Movement"));
	ProyectileMovement->InitialSpeed = MovementSpeed;
	ProyectileMovement->MaxSpeed = MovementSpeed;

	// Projectile particle trail 
	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AProyectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Play launch sound when you fire the weapon
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	
}

void AProyectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();

	// Avoid nullprt crash in case there is no Owner
	if(!MyOwner)
	{
		return;
	}
	// If the other actor isn't self  OR owner AND exist then apply damage
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(),
			this, DamageType);
		
		// Play effects 
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);

	}

	// Destroy the object to avoid flying bullets after collision
	Destroy();

}

