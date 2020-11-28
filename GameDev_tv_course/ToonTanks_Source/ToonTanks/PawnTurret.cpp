// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimeHandle, this, &APawnTurret::CheckFireCondition, FireRate, true, false);	

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	if(ReturnDistanceToPlayer() <= (2*FireRange) )
	{
		RotateTurret(PlayerPawn->GetActorLocation());
	}
	
	
}

// Called to bind functionality to input
void APawnTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawnTurret::CheckFireCondition()
{

	// If player == null || player == dead then not fire
	if(!PlayerPawn )
	{ // || !PlayerPawn->GetIsPlayerAlive()
		return;
	}
	// If player is within range then fire 
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		//Fire
		Fire();
		// Log Fire event
		//UE_LOG(LogTemp, Warning, TEXT("FIRE!!!"));
	}

}

float APawnTurret::ReturnDistanceToPlayer()
{
	// Protect the pointer from null crashes
	if(!PlayerPawn)
	{
		return 0.0f;
	}

	float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size();

	return Distance;
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}