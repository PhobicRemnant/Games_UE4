// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"

class USpringArmComponent;
class UCameraComponent;

APawnTank::APawnTank()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Movement functions 
	Rotate();
	Move();

	//nullptr protection
	if(PlayerControllerRef)
	{
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Camera, true, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;

		RotateTurret(HitLocation);
	}
}	

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("Move Forward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotationInput);
	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}
void APawnTank::CalculateRotationInput(float Value)
{
	// Calculate the rotation of the gun turret
	float RotateAmount = Value * RotationSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	// Frontal/Backwards movement
	AddActorLocalOffset(MoveDirection, true);
}
void APawnTank::Rotate()
{
	// Tank rotation 
	AddActorLocalRotation(RotationDirection, true);
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	// Hide player - TO DO -> add death sound

	// Declare player status as dead
	bIsPlayerAlive = false;

	// Hide actor in game world
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
}

bool APawnTank::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}