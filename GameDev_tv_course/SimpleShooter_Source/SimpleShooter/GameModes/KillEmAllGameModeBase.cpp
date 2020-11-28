// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h" 
#include "../ShooterAIController.h"
void AKillEmAllGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	UE_LOG(LogTemp, Warning, TEXT("A Pawn was killed"));

	// If player dies
	APlayerController* PlayerController = 	Cast<APlayerController>(PawnKilled->GetController());

	if(PlayerController != nullptr)
	{
		//PlayerController->GameHasEnded(nullptr, false);
		EndGame(false);
	}

	// Iterate over the AI Enemies in-world
	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		// Is not Dead?
		if (!Controller->IsDead())
		{
			return;
		}
	}

	// End game as a victory
	EndGame(true);
}

void AKillEmAllGameModeBase::EndGame(bool bIsPlayerWinner)
{
	
	for( AController* Controller : TActorRange<AController>(GetWorld()) )
	{
		bool bIsWinner = ( Controller->IsPlayerController() == bIsPlayerWinner );
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);

	}

}