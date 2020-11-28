// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
		virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool IsWinner = false) override;

private:

	// Restart time of the game, 5s
	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.0f;

	// Handler to restart the game
	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY()
	UUserWidget* HUD;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
