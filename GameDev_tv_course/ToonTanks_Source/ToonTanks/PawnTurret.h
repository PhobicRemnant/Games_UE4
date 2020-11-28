// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.h"	
#include "PawnTurret.generated.h"

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

public:

	//APawnTurret();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void HandleDestruction() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Properties", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Properties", meta = (AllowPrivateAccess = "true"))
	float FireRange= 200.0f;

	void CheckFireCondition();

	APawnTank* PlayerPawn;
	FTimerHandle FireRateTimeHandle;

	float ReturnDistanceToPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
