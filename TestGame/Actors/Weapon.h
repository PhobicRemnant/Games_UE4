// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "Weapon.generated.h"

UCLASS()
class TESTGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Shoot gun
	void PullTrigger();



private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	//UPROPERTY(EditAnywhere)
	//UParticleSystem* MuzzleFlash;

	//UPROPERTY(EditAnywhere)
	//UParticleSystem* BulletCollision;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	float Weight = 5.0f;

	// 5m default range
	UPROPERTY(EditAnywhere)
	float Range = 500.0f;

	UPROPERTY(EditAnywhere)
	FString weaponType = "None";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Proyectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABullet> BulletType;

	AController* GetWeaponController() const;

	//UPROPERTY(EditAnywhere)
	//USoundBase* MuzzleSound;

	//UPROPERTY(EditAnywhere)
	//USoundBase* ImpactSound;

};
