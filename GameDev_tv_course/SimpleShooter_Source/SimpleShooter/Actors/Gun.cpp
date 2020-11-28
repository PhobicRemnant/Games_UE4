// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h" 

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{	 
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	// Shoot log
	UE_LOG(LogTemp, Warning, TEXT("Shooty Shooty"));

	FHitResult Hit;
	FVector ShotDirection;

	bool bSuccess = GunTrace(Hit, ShotDirection);

	if(bSuccess)
	{


//		DrawDebugPoint(GetWorld(), Hit.Location, 10, FColor::Red, true);
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletCollision, Hit.Location, ShotDirection.Rotation()  );
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location );

		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);

		AActor* HitActor = Hit.GetActor();

		AController* OwnerController = GetGunController();
		if (!OwnerController)
		{
			return;
		}

		if(HitActor != nullptr)
		{
			HitActor->TakeDamage(Damage, DamageEvent,OwnerController , this);
		}

		
	}

	// Play the firing effects and sound
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{


	// Variables for the out parameters in "GetPlayerViewpoint()"
	FVector Location;
	FRotator Rotation;

	AController* OwnerController = GetGunController();
	if(!OwnerController)
	{
		return false;
	}

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;
	// TODO lineTracing
	ShotDirection = -Rotation.Vector();

	FCollisionQueryParams Params;
	// Avoid bullet collision with itself (gun)
	Params.AddIgnoredActor(this);
	// Avoid bullet collision with the shooter 
	Params.AddIgnoredActor(GetOwner());


	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

}

AController* AGun::GetGunController() const 
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	// NullPtr Protection
	if (!OwnerPawn) 
	{
		return nullptr; 
	}

	return OwnerPawn->GetController();
}	