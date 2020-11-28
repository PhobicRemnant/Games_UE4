// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainCharacter.generated.h"


UCLASS()
class TESTGAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AMainCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Attack function
	void Attack();

	bool bAim = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;

	float Health;

	UPROPERTY(EditAnywhere)
	float ZoomSpeed = 1.0f;
	float AimOffArmLen = 300.0f;
	float AimOnArmLen = 100.0f;

	void MoveForward(float AxisValue);
	void MoveSideways(float AxisValue);


	// Weapon Object
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;
	
	UFUNCTION(BlueprintCallable)
	bool GetAimStatus() { return bAim; }

	UPROPERTY()
	AWeapon* Weapon;

	UFUNCTION()
	void AimOn();

	UFUNCTION()
	void AimOff();

};


