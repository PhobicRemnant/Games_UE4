// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(Root);

	ProjectileSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(WeaponMesh);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWeapon::PullTrigger()
{
	// Shoot log
	UE_LOG(LogTemp, Warning, TEXT("Shooty Shooty"));
	
	// Spawn bullet at the point of the barrel
	if(BulletType)
	{
		
		AController* OwnerController = GetWeaponController();
		if (!OwnerController)
		{
			return;
		}
				
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		
		// Spawn bullet
		ABullet* NewBullet = GetWorld()->SpawnActor<ABullet>(BulletType,	ProjectileSpawnPoint->GetComponentLocation(),
			OwnerController->GetControlRotation(),
																			SpawnParameters);
		// Avoid crashy crash
		if (NewBullet)
		{
			NewBullet->SetOwner(this);
			// Play bullet sound
			UGameplayStatics::SpawnSoundAttached(NewBullet->FireSound, WeaponMesh, TEXT("Weapon Mesh"));
		}

		
	}

}

AController* AWeapon::GetWeaponController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if(!OwnerPawn)
	{
		return nullptr;
	}

	return OwnerPawn->GetController();
}
