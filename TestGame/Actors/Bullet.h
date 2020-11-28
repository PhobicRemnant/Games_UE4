// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Bullet.generated.h"


UCLASS()
class TESTGAME_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// COMPONENTS

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;

	// VARIABLES

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 50.0f;

	// PARTICLE EFFECTS

	//UPROPERTY(EditAnywhere, Category = "Effects", meta = (AllocwPrivateAccess = "true"))
	//UParticleSystem* HitParticle;

	//UPROPERTY(EditAnywhere, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	//UParticleSystemComponent* ParticleTrail;

	//UPROPERTY(EditAnywhere, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<UCameraShake> HitShake;

	// AUDIO

	//UPROPERTY(EditAnywhere, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	//USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Audio", meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			FVector NormalImpulse, const FHitResult& Hit);

};
