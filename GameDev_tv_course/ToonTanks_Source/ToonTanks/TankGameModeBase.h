// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerControllerBase.h"
#include "PawnTurret.h"
#include "PawnTank.h"
#include "TankGameModeBase.generated.h"
	
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor* DeadActor);

	

private:

	int32 GetTargetTurretCount();

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

	APawnTank* PlayerTank;
	APlayerControllerBase* PlayerControllerRef;
	int32 TargetTurrets = 0;


protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool PlayerWon);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop	", meta = (AllowPrivateAccess = "true"))
	int32 StartDelay = 0;
};
