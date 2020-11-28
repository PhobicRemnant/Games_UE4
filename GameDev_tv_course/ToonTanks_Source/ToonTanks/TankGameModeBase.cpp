// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	// Get references and game win/lose conditions 

	// Call HandleGameStart to initialize game
	HandleGameStart();
	
}	

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
		//Check what type of actor died.
		//If Turret then tally.
		//If Player then go to lose condition.
		if(DeadActor == PlayerTank)
		{
			PlayerTank->HandleDestruction();
			HandleGameOver(false);

			if(PlayerControllerRef)
			{
				PlayerControllerRef->SetPlayerEnabledState(false);
			}
		}
		else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
		{
			DestroyedTurret->HandleDestruction();

			if (--TargetTurrets == 0)
			{
				HandleGameOver(true);
			}
		}
	UE_LOG(LogTemp, Warning, TEXT("A Pawn died."));
}
void ATankGameModeBase::HandleGameStart()
{
	// Call HandleGameStart to initialize game
	// Call BP implementation GameStart()

	// Get all Turret actors in world
	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();
	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);
	
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, 
			&APlayerControllerBase::SetPlayerEnabledState, true);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);

	}

}
void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// See if player has destroyed all the turrets, show win result.
	// If turrets destroyed the player show lose result 
	// Call BP implementation 
	GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	// Get Turret Actors in the world
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}