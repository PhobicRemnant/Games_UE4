// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if(AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		// Get starting player location
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		// Get starting AIPawn location
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// The Following lines are commented since the AI Behavior is implementes with blackboard trees functionality

	// APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	/*

	// If in LOS
	if(LineOfSightTo(PlayerPawn))
	{
		// Get the player location 
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		// Get the same player location in case the player dissapears
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());

	}
	else // if not in LOS 
	{
		// Go to the last known player location
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));

	}

	*/
}


bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());

	if(ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}